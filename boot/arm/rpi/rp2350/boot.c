#include <ctype.h>
#include <pico.h>
#include <pico/bootrom.h>
#include <pico/platform/common.h>
#include <pico/stdio.h>
#include <plex/kernel.h>
#include <plex/macros.h>
#include <plex/types.h>
#include <string.h>

#if BCONFIG_ARM_RPI_RP2350_USB_STDIO_WAIT_DELAY_MS > 0
#define PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS                                 \
  BCONFIG_ARM_RPI_RP2350_USB_STDIO_WAIT_DELAY_MS
#endif

#if BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 1
#include <pico/stdio_usb.h>
#elif BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 2
#include <pico/stdio_rtt.h>
#elif BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 3
#include <pico/stdio_uart.h>
#elif BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 4
#endif

#if defined BCONFIG_KERNEL_CMDLINE
#define KERNEL_CMDLINE TOSTRING(BCONFIG_KERNEL_CMDLINE)
#else
#define KERNEL_CMDLINE ""
#endif

#define CURRENT_FAMILY                                                         \
  TOSTRING(PLEX_FAMILY) " " TOSTRING(PLEX_PLATFORM) " (" TOSTRING(PLEX_ARCH) ")"

internal bool check_stdio() {
#if BCONFIG_ARM_RPI_RP2350_ENABLE_STDIO
#if BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 1
  return stdio_usb_init();
#elif BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 2
  return stdio_rtt_init();
#elif BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 3
  return stdio_uart_init();
#elif BCONFIG_ARM_RPI_RP2350_STDIO_MODE == 4
  return stdio_init_all();
#endif
#endif // BCONFIG_ARM_RPI_RP2350_ENABLE_STDIO

  return false;
}

char cmdline[4096] = {0};

internal int read_input(char *buffer, size_t buffer_size) {
  int idx = 0, c = 0;

  if (buffer_size <= 0)
    return 0;

  while (1) {
    if (idx >= buffer_size - 1)
      break;

    stdio_printf("\r> ");

    if (idx > 0) {
      stdio_put_string(buffer, idx, false, false);
    }

    stdio_flush();

    c = stdio_getchar();
    stdio_putchar(c);

    if (c == '\n' || c == '\r') {
      buffer[idx] = 0;

      break;
    }

    if (!iscntrl(c)) {
      buffer[++idx - 1] = c;
      stdio_flush();

      continue;
    }

    if (c == 0x08 || c == 0x7f && idx > 0) { // Backspace key
      // Overwrite the old character and decrement the
      buffer[idx-- - 1] = 0;

      stdio_putchar(0x08); // Backspace character
      stdio_putchar(' ');  // Space to delete old character
      stdio_flush();       // Print the buffered output
    }
  }

  stdio_puts("");

  return idx - 1;
}

internal void boot_menu(kernel_init_info_t *info) {
  // Wait for a character to be entered
  fgetc(stdin);

  puts("Plex Boot Menu for " CURRENT_FAMILY);

  while (1) {
    puts("Options:");
    puts("1. Boot");
    printf("2. Set kernel command-line (current: %s)\n", info->command_line);
    puts("3. Reboot to BOOTSEL mode");

    printf("> ");
    int c = fgetc(stdin);

    c -= '0'; // Get option number

    if (c > 3 || c < 1) {
      puts("\nERROR: invalid option");

      continue;
    }

    if (c == 1) {
      break;
    }

    if (c == 2) {
      puts("\nPlease input the new kernel command line:");

      read_input(cmdline, sizeof(cmdline));
      info->command_line = cmdline;
    }

    if (c == 3) {
      reset_usb_boot(0, 1);

      // This should never return.
      for (;;)
        ;
    }
  }

  puts("\nBooting...");
}

int main() {
  kernel_init_info_t info = {0};

  bool has_stdio = check_stdio();
  const char *kernel_cmdline = KERNEL_CMDLINE;

  info.command_line = kernel_cmdline;

  if (has_stdio) {
    boot_menu(&info);
  }

  kernel_main(&info);

  // HANG
  for (;;)
    tight_loop_contents();
}
