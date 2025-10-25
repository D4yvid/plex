project(kernel C CXX ASM)

list(APPEND KERNEL_SOURCES "init/main.c")

include("${PROJECT_SOURCE_DIR}/arch/${KERNEL_ARCH}/${KERNEL_FAMILY}/sources.cmake")

add_library(kernel
  STATIC ${KERNEL_SOURCES}
)

target_include_directories(kernel
  PUBLIC ${KERNEL_INCLUDE_DIRECTORIES} "${PROJECT_SOURCE_DIR}/include"
  INTERFACE "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(kernel
  PUBLIC ${KERNEL_LIBRARIES}
)

target_compile_definitions(kernel
  PUBLIC ${KERNEL_DEFINES}
)
