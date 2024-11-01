# cmake 3.22 is necessary to have FindCUDAToolkit.cmake
cmake_minimum_required(VERSION 3.22)


project(hello_picus LANGUAGES CXX C)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()


# #####################################################################
# enable_language(CUDA)

# # FindCUDAToolkit.cmake is able to correctly find cuda library
# # either when using nvcc from cuda toolkit or nvc++ from nvhpc
# # only in cmake 3.22.0
# if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.22.0" )
#   message("Using CUDAToolkit macros")
#   find_package(CUDAToolkit REQUIRED)
# else()
#   message("Using CUDALibs macros")
#   find_package(CUDALibs REQUIRED COMPONENTS CUBLAS)
# endif()

# if(NOT DEFINED CMAKE_CUDA_STANDARD)
#   set(CMAKE_CUDA_STANDARD 11)
# endif()
# set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# # other third party libraries
# find_package(OpenMP)
# #find_package(OpenGL)
# #find_package(GLUT)

# # we also need extra stuff to make sure compile flags are correctly
# # passed to nvcc / host compiler
# include(protect_nvcc_flags)
# include(protect_pthread_flag)

# ##########################################################

add_subdirectory(src)
