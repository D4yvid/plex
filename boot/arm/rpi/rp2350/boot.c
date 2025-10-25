#include <pico.h>
#include <pico/stdio_usb.h>
#include <plex/kernel.h>
#include <stdio.h>

int main() {
  stdio_usb_init();

  // Wait for character to boot
  fgetc(stdin);

  kernel_init_info_t info = {
      .print = printf,
      .command_line = "log=1",
  };

  kernel_main(&info);

  // HANG
  for (;;)
    ;
}
