#include <plex/log.h>
#include <stdarg.h>

/** The variable in which the platform will define to set the logger */
external klogger_platform_interface_t platform;

internal bool initialized = false;

klogger_error_t klogger_init() {
  if (!platform.init()) {
    return ENO_LOGGER_IMPL;
  }

  initialized = true;
  return 0;
}

klogger_error_t klogger_set_log_level(klogger_log_level_t level) {
  if (!initialized)
    return ENO_LOGGER_IMPL;

  platform.set_log_level(level);

  return 0;
}

klogger_error_t klogger_deinit() {
  if (!initialized)
    return ENO_LOGGER_IMPL;

  platform.deinit();

  return 0;
}

[[gnu::format(printf, 2, 3)]]
void printk(klogger_log_level_t level, const char *fmt, ...) {
  if (!initialized)
    return;

  va_list args;

  va_start(args, fmt);

  platform.log(level, fmt, args);

  va_end(args);
}
