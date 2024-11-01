#include <iostream>
#include "common/gpios.h"
int main(int argc, char **argv)
{
    std::cout << "Hello Picus!" << std::endl;

    GPIOS gpios;
    gpios.setGPIOCallback([]()
                          { std::cout << "a gpio changed!" << std::endl; });
    gpios.init();

    gpios.set_output(GPIO_PIN::OUT2, 1);

    return 0;
}