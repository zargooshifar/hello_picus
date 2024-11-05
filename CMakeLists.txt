# cmake 3.22 is necessary to have FindCUDAToolkit.cmake
cmake_minimum_required(VERSION 3.8)


project(hello_picus LANGUAGES CUDA CXX C)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Find OpenCV with CUDA support
find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)

# Set CUDA architecture (modify according to your GPU)
# set(CUDA_ARCH_BIN "12.2" CACHE STRING "CUDA architecture bin")

# Include OpenCV and CUDA directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CUDA_INCLUDE_DIRS})
# find gpiod lib for controlling gpios
find_package(gpiod REQUIRED)

# #####################################################################

# ##########################################################

# gpio example
add_executable(gpio_example
  src/gpio_example.cpp
  src/common/picus_gpios.h
  src/common/gpios.h
  src/common/gpios.cpp)

target_link_libraries(gpio_example
  gpiod
)



# cuda example
add_executable(cuda_example
  src/cuda_example.cpp)


# Enable separable compilation for CUDA (optional, depending on your needs)
set_property(TARGET cuda_example PROPERTY CUDA_SEPARABLE_COMPILATION ON)

# Link OpenCV and CUDA libraries
target_link_libraries(cuda_example ${OpenCV_LIBRARIES} ${CUDA_LIBRARIES})

