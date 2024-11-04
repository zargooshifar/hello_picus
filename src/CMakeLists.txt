add_executable(hello_picus
     main.cpp
     common/picus_gpios.h
     common/gpios.h
     common/gpios.cpp)

target_link_libraries(hello_picus
    gpiod
)