cmake_minimum_required(VERSION 3.26)
project(Minigin)

# list source files here
add_executable(minigin WIN32
  Minigin/Font.cpp
  Minigin/Font.h
  Minigin/GameObject.cpp
  Minigin/GameObject.h
  Minigin/InputManager.cpp
  Minigin/InputManager.h
  Minigin/Main.cpp
  Minigin/Minigin.cpp
  Minigin/Minigin.h
  Minigin/Renderer.cpp
  Minigin/Renderer.h
  Minigin/ResourceManager.cpp
  Minigin/ResourceManager.h
  Minigin/Scene.cpp
  Minigin/Scene.h
  Minigin/SceneManager.cpp
  Minigin/SceneManager.h
  Minigin/TextObject.cpp
  Minigin/TextObject.h
  Minigin/Texture2D.cpp
  Minigin/Texture2D.h
  Minigin/Transform.cpp
  Minigin/Transform.h
)

# enable c++20 features
target_compile_features(minigin PUBLIC cxx_std_20)
# compile at warning level 4 + treat warnings as errors
target_compile_options(minigin PRIVATE /W4 /WX)
# set minigin as the default startup project
set_property(TARGET minigin PROPERTY VS_STARTUP_PROJECT minigin)

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
  DOWNLOAD_NO_PROGRESS ON # Disable progress bar to reduce output clutter
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads # Set download directory to avoid cluttering source tree
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  set(GLM_INCLUDE_DIR "${glm_SOURCE_DIR}")
endif()

# add SDL2
FetchContent_Declare(
  SDL2
  URL https://www.libsdl.org/release/SDL2-devel-2.26.3-VC.zip # Replace with the desired version URL
  DOWNLOAD_NO_PROGRESS ON # Disable progress bar to reduce output clutter
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads # Set download directory to avoid cluttering source tree
)
FetchContent_GetProperties(SDL2)
if(NOT SDL2_POPULATED)
  FetchContent_Populate(SDL2)
  set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
  set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
else()
  set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
  set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
endif()
endif()

# add SDL2_image
FetchContent_Declare(
  SDL2_image
  URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.6.3-VC.zip # Replace with the desired version URL
  DOWNLOAD_NO_PROGRESS ON # Disable progress bar to reduce output clutter
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads # Set download directory to avoid cluttering source tree
)
FetchContent_GetProperties(SDL2_image)
if(NOT SDL2_image_POPULATED)
  FetchContent_Populate(SDL2_image)
  set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
  set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
else()
  set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
  set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
endif()
endif()

# add SDL2_ttf
FetchContent_Declare(
  SDL2_ttf
  URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.2-VC.zip # Replace with the desired version URL
  DOWNLOAD_NO_PROGRESS ON # Disable progress bar to reduce output clutter
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads # Set download directory to avoid cluttering source tree
)
FetchContent_GetProperties(SDL2_ttf)
if(NOT sdl2_ttf_POPULATED)
  FetchContent_Populate(SDL2_ttf)
  set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
  set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
else()
  set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
  set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
endif()
endif()

set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
IF(EXISTS ${VLD_DIR})
  set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
  else()
      set(VLD_LIBRARY "${VLD_DIR}/lib/Win86/vld.lib")
  endif()
endif()

# set all include directories
target_include_directories(minigin PRIVATE
    ${CMAKE_SOURCE_DIR}/Minigin/
    ${VLD_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR})

# set libraries to link with
target_link_libraries(minigin ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${VLD_LIBRARY})

# add post build commands
add_custom_command(TARGET minigin POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:minigin>"
)
add_custom_command(TARGET minigin POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:minigin>"
)
add_custom_command(TARGET minigin POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:minigin>"
)
add_custom_command(TARGET minigin POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:minigin>/Data"
)