# Fakes Findharfbuzz.cmake for Emscripten
set(harfbuzz_FOUND TRUE)
set(harfbuzz_VERSION "3.0.0")

if(NOT TARGET harfbuzz::harfbuzz)
  add_library(harfbuzz::harfbuzz INTERFACE IMPORTED)
endif()
