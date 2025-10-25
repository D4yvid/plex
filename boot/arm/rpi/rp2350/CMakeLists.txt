project(plex-rp2350 C CXX ASM)

add_executable(plex-rp2350 boot.c)
target_link_libraries(plex-rp2350 PUBLIC
  pico_stdlib
  pico_stdio_usb
  kernel)

pico_add_extra_outputs(plex-rp2350)
