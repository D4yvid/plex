project(plex-rp2350 C CXX ASM)

if (BCONFIG_ARM_RPI_RP2350_ENABLE_STDIO AND NOT "${BCONFIG_ARM_RPI_RP2350_STDIO_MODE}" EQUAL 0)
  list(APPEND EXTRA_LIBS "pico_stdio")

  if ("${BCONFIG_ARM_RPI_RP2350_STDIO_MODE}" EQUAL 1)
    list(APPEND EXTRA_LIBS "pico_stdio_usb")
  elseif ("${BCONFIG_ARM_RPI_RP2350_STDIO_MODE}" EQUAL 2)
    list(APPEND EXTRA_LIBS "pico_stdio_rtt")
  elseif ("${BCONFIG_ARM_RPI_RP2350_STDIO_MODE}" EQUAL 3)
    list(APPEND EXTRA_LIBS "pico_stdio_uart")
  elseif ("${BCONFIG_ARM_RPI_RP2350_STDIO_MODE}" EQUAL 4)
    list(APPEND EXTRA_LIBS "pico_stdio_usb")
    list(APPEND EXTRA_LIBS "pico_stdio_rtt")
    list(APPEND EXTRA_LIBS "pico_stdio_uart")
  endif ()
endif ()

add_executable(plex-rp2350 boot.c)
target_link_libraries(plex-rp2350 PUBLIC
  pico_stdlib
  ${EXTRA_LIBS}
  kernel)

target_compile_definitions(plex-rp2350 PUBLIC
  ${BOOT_DEFINES})

pico_add_extra_outputs(plex-rp2350)
