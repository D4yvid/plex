#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <plex/kernel/logger.h>
#include <plex/types.h>

typedef enum kmemory_map_entry_permission_t {
  MEMORY_MAP_ENTRY_USABLE,
  MEMORY_MAP_ENTRY_RESERVED
} kmemory_map_permission_t;

typedef struct kmemory_map_entry_t {
  kmemory_map_permission_t type; //< The type of this entry
  size_t size;                   //< The size of this entry
  void *address;                 //< The address of the beginning of the entry
} kmemory_map_entry_t;

typedef struct kmemory_map_t {
  kmemory_map_entry_t *entries; //< The memory map entries
  size_t entry_count; //< How many memory entries are in the memory map
} kmemory_map_t;

typedef struct kernel_init_info_t {
  const char *command_line; //< The kernel command-line to boot
  kmemory_map_t memory_map; //< The memory map of this device
} kernel_init_info_t;

[[noreturn]]
external void kernel_main(kernel_init_info_t *info);

#endif /** __KERNEL_H__ */
