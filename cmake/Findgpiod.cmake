include(FetchContent)
FetchContent_Declare(
  libgpiod_content
  GIT_REPOSITORY https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git
  GIT_TAG v1.6.3
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)

FetchContent_MakeAvailable(libgpiod_content)

configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/libgpiod_config.h.in
    ${PROJECT_BINARY_DIR}/libgpiod_config.h
)

set(GPIOD_INCLUDES ${libgpiod_content_SOURCE_DIR}/include)
# Add include directories
include_directories(${GPIOD_INCLUDES})

# Add source files from the lib folder
set(GPIOD_SOURCES
    ${libgpiod_content_SOURCE_DIR}/lib/core.c
    ${libgpiod_content_SOURCE_DIR}/lib/ctxless.c
    ${libgpiod_content_SOURCE_DIR}/lib/helpers.c
    ${libgpiod_content_SOURCE_DIR}/lib/iter.c
    ${libgpiod_content_SOURCE_DIR}/lib/misc.c

)
include_directories(cmake/)

# Create the shared library
add_library(gpiod SHARED ${GPIOD_SOURCES})

target_compile_options(gpiod PRIVATE
    -include ${CMAKE_BINARY_DIR}/libgpiod_config.h
)