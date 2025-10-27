#include <plex/kernel/logger.h>

internal klogger_log_level_t current_level = LOG_LEVEL_TRACE;

internal bool rp2350_logger_init() {
  bool has_stdio = false;

  // TODO: initialize STDIO with drivers

  return true;
}

internal void rp2350_logger_log(klogger_log_level_t level, const char *fmt,
                                va_list args) {
  if (level < current_level)
    return;
}

internal void rp2350_logger_set_level(klogger_log_level_t level) {
  current_level = level;
}

internal bool rp2350_logger_deinit() {
  ;

  return true;
}

klogger_platform_interface_t platform = {
    .init = rp2350_logger_init,
    .deinit = rp2350_logger_deinit,
    .log = rp2350_logger_log,
    .set_log_level = rp2350_logger_set_level,
};
