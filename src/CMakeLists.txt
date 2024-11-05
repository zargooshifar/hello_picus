# gpio example
add_executable(gpio_example
    gpio_example.cpp
     common/picus_gpios.h
     common/gpios.h
     common/gpios.cpp)

target_link_libraries(gpio_example
    gpiod
)



# cuda example
add_executable(cuda_example
    cuda_example.cpp)


# Enable separable compilation for CUDA (optional, depending on your needs)
set_property(TARGET cuda_example PROPERTY CUDA_SEPARABLE_COMPILATION ON)

# Link OpenCV and CUDA libraries
target_link_libraries(cuda_example ${OpenCV_LIBRARIES} ${CUDA_LIBRARIES})