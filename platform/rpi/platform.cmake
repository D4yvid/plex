if ("${PLEX_ARCH}" STREQUAL "arm" AND "${PLEX_PLATFORM}" STREQUAL "rp2350")
  set(PICO_PLATFORM "rp2350-arm-s")
else ("${PLEX_ARCH}" STREQUAL "riscv" AND "${PLEX_PLATFORM}" STREQUAL "rp2350")
  set(PICO_PLATFORM "rp2350-riscv")
endif ()

include("${CMAKE_SOURCE_DIR}/external/pico_sdk_import.cmake")

pico_sdk_init()
