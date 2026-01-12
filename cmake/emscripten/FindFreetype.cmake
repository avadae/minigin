# Fakes FindFreetype.cmake for Emscripten
set(FREETYPE_FOUND TRUE)
set(FREETYPE_VERSION_STRING "2.10.0")

if(NOT TARGET Freetype::Freetype)
  add_library(Freetype::Freetype INTERFACE IMPORTED)
  # Emscripten handles linking via -s USE_FREETYPE=1, but we might need to be explicit if this target is linked directly.
  # However, -s flags are usually compile/link options.
  # We assume the user or toolchain adds -s USE_FREETYPE=1 to CMAKE_C_FLAGS/CMAKE_CXX_FLAGS
endif()
