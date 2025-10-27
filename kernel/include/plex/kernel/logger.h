#ifndef __KERNEL_LOG_H__
#define __KERNEL_LOG_H__

#include <plex/types.h>
#include <stdio.h>

/**
 * All log levels
 */
typedef enum klogger_log_level_t {
  LOG_LEVEL_TRACE,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_CRITICAL,
} klogger_log_level_t;

/**
 * Logger errors
 */
typedef enum klogger_error_t {
  ENO_LOGGER_IMPL = 1,
} klogger_error_t;

/**
 * The logger interface in which the platform loggers will implement
 */
typedef struct klogger_platform_interface_t {
  /**
   * Initializes this logger platform
   *
   * @return true if the platform is initialized successfully
   */
  bool (*init)(void);

  /**
   * Deinitializes this logger platform
   *
   * @return true if the platform is initialized successfully
   */
  bool (*deinit)(void);

  /**
   * Log a message using the level
   *
   * @param[level] The log level to use
   * @param[fmt]   The format string to log
   * @param[args]  The format string arguments
   */
  void (*log)(klogger_log_level_t level, const char *fmt, va_list args);

  /**
   * Set the logger log level
   *
   * @param[level] The new log level to use
   */
  void (*set_log_level)(klogger_log_level_t level);
} klogger_platform_interface_t;

/**
 * Initializes the kernel logger using the platform implementation.
 *
 * @return ENO_LOGGER_IMPL if any logger is available to use
 */
external klogger_error_t klogger_init();

/**
 * Set the new log level for this logger
 *
 * @param[level] The new log level to set
 * @return ENO_LOGGER_IMPL if no logger is implemented
 */
external klogger_error_t klogger_set_log_level(klogger_log_level_t level);

/**
 * Deinitializes the kernel logger (this will probably never be called anyway)
 *
 * @return ENO_LOGGER_IMPL if no logger is implemented
 */
external klogger_error_t klogger_deinit();

/**
 * Print to the kernel logger
 *
 * @param[level] The log level to log into
 * @param[fmt]   The format string
 */
[[gnu::format(printf, 2, 3)]]
external void printk(klogger_log_level_t level, const char *fmt, ...);

#endif /** __KERNEL_LOG_H__ */
