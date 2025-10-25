#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <plex/types.h>

typedef struct kernel_init_info_t {
  const char *command_line;
  int (*print)(const char *, ...);
} kernel_init_info_t;

[[noreturn]]
external void kernel_main(kernel_init_info_t *info);

#endif /** __KERNEL_H__ */
