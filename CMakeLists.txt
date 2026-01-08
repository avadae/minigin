cmake_minimum_required(VERSION 3.26)
project(Minigin)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
  set(TARGET_NAME minigin_web)
  set(TARGET_PARAM )
else()
  set(TARGET_NAME minigin)
  set(TARGET_PARAM WIN32)
endif()

# list source files here
add_executable(${TARGET_NAME} ${TARGET_PARAM}
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
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
# set minigin as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

# add SDL3
if (WIN32)
  FetchContent_Declare(
    SDL3
    URL https://www.libsdl.org/release/SDL3-devel-3.4.0-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_GetProperties(SDL3)
  if(NOT SDL3_POPULATED)
    FetchContent_Populate(SDL3)
  set(SDL3_INCLUDE_DIR ${sdl3_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL3_LIBRARIES "${sdl3_SOURCE_DIR}/lib/x64/SDL3.lib")
    set(SDL3_LIBRARY_DLL "${sdl3_SOURCE_DIR}/lib/x64/SDL3.dll")
  else()
    set(SDL3_LIBRARIES "${sdl3_SOURCE_DIR}/lib/x86/SDL3.lib")
    set(SDL3_LIBRARY_DLL "${sdl3_SOURCE_DIR}/lib/x86/SDL3.dll")
  endif()
  endif()

  # add SDL3_image
  FetchContent_Declare(
    SDL3_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL3_image-devel-3.2.6-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL3_image)
  if(NOT SDL3_image_POPULATED)
    FetchContent_Populate(SDL3_image)
    set(SDL3_IMAGE_INCLUDE_DIR ${sdl3_image_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL3_IMAGE_LIBRARIES "${sdl3_image_SOURCE_DIR}/lib/x64/SDL3_image.lib")
    set(SDL3_IMAGE_LIBRARY_DLL "${sdl3_image_SOURCE_DIR}/lib/x64/SDL3_image.dll")
  else()
    set(SDL3_IMAGE_LIBRARIES "${sdl3_image_SOURCE_DIR}/lib/x86/SDL3_image.lib")
    set(SDL3_IMAGE_LIBRARY_DLL "${sdl3_image_SOURCE_DIR}/lib/x86/SDL3_image.dll")
  endif()
  endif()

  # add SDL3_ttf
  FetchContent_Declare(
    SDL3_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL3_ttf-devel-3.1.0-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL3_ttf)
  if(NOT SDL3_ttf_POPULATED)
    FetchContent_Populate(SDL3_ttf)
    set(SDL3_TTF_INCLUDE_DIR ${sdl3_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL3_TTF_LIBRARIES ${sdl3_ttf_SOURCE_DIR}/lib/x64/SDL3_ttf.lib)
    set(SDL3_TTF_LIBRARY_DLL "${sdl3_ttf_SOURCE_DIR}/lib/x64/SDL3_ttf.dll")
  else()
    set(SDL3_TTF_LIBRARIES ${sdl3_ttf_SOURCE_DIR}/lib/x86/SDL3_ttf.lib)
    set(SDL3_TTF_LIBRARY_DLL "${sdl3_ttf_SOURCE_DIR}/lib/x86/SDL3_ttf.dll")
  endif()
  endif()

  find_package(VLD CONFIG)

  # set all include directories
  target_include_directories(${TARGET_NAME} PRIVATE
    ${VLD_INCLUDE_DIR}
    ${SDL3_INCLUDE_DIR} 
    ${SDL3_IMAGE_INCLUDE_DIR} 
    ${SDL3_TTF_INCLUDE_DIR})
  
  # set libraries to link with
  target_link_libraries(${TARGET_NAME} PUBLIC
    ${SDL3_LIBRARIES} 
    ${SDL3_IMAGE_LIBRARIES} 
    ${SDL3_TTF_LIBRARIES} 
    ${VLD_LIBRARY}
  )

elseif(NOT EMSCRIPTEN)

  FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL3)
  
  FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.6
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL3IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL3_image)

  FetchContent_Declare(
    SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-3.1.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL3TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL3_ttf)

  target_include_directories("${TARGET_NAME}" PUBLIC 
    ${sdl3_SOURCE_DIR}/include
    ${sdl3_image_SOURCE_DIR}/include
    ${sdl3_ttf_SOURCE_DIR}
  )
  target_link_libraries("${TARGET_NAME}" PUBLIC 
    SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf
  )
endif()

target_include_directories(${TARGET_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/Minigin/
  ${glm_SOURCE_DIR}
)

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=3 -sUSE_SDL_IMAGE=3 -sUSE_SDL_TTF=3 -g")
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=3 -sUSE_SDL_IMAGE=3 -sUSE_SDL_TTF=3 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" -sSDL3_IMAGE_FORMATS=['tga','png']")

  # work around https://github.com/emscripten-core/emscripten/issues/11513
  set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -fno-stack-protector")

  # Use the Emscripten toolchain
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EmscriptenToolchain.cmake)

  # Additional settings for Emscripten build
  set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
      LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )

  # Have emscripten generate a html page too.
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  
elseif(WIN32)
  set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")

  # add post build commands
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL3_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL3_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL3_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
endif()
