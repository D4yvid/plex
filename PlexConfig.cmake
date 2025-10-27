file(
  STRINGS PlexConfig PLEX_CONFIG
  REGEX "^[^#]"
)

list(LENGTH PLEX_CONFIG PLEX_CONFIG_COUNT)

foreach (PCFG_STRING ${PLEX_CONFIG})
  string(REPLACE "=" ";" PCFG_LIST "${PCFG_STRING}")

  list(GET PCFG_LIST 0 KEY)
  list(GET PCFG_LIST 1 VALUE)

  if ("${VALUE}" STREQUAL "")
    continue()
  endif()

  set("${KEY}" ${VALUE})

  string(FIND "${KEY}" "KCONFIG" KCONFIG_OUT)
  string(FIND "${KEY}" "BCONFIG" BCONFIG_OUT)

  if ("${KCONFIG_OUT}" EQUAL 0)
    list(APPEND KERNEL_DEFINES "${KEY}=${VALUE}")
  elseif ("${BCONFIG_OUT}" EQUAL 0)
    list(APPEND BOOT_DEFINES "${KEY}=${VALUE}")
  else ()
    add_compile_definitions("${KEY}=${VALUE}")
  endif ()
endforeach ()

message("Plex configuration (${PLEX_CONFIG_COUNT}): ${PLEX_CONFIG}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
