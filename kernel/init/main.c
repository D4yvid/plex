#include <plex/kernel.h>

[[noreturn]]
void kernel_main(kernel_init_info_t *info) {
  info->print("commandline: %s\n", info->command_line);

  for (;;)
    ;
}
