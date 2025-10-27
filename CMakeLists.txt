cmake_minimum_required(VERSION 3.12)

include(PlexConfig.cmake)
include("${CMAKE_SOURCE_DIR}/platform/${PLEX_FAMILY}/platform.cmake")

project(plex C CXX ASM)

set(COMMON_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/common/include")

include_directories("${COMMON_INCLUDE_DIR}")

add_subdirectory(kernel)
add_subdirectory(boot)

