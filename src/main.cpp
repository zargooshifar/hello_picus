#include <iostream>
#include "common/gpios.h"
#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>

int main(int argc, char **argv)
{
    std::cout << "Hello Picus!" << std::endl;

    GPIOS gpios;
   
    gpios.setGPIOCallback([]() -> void { std::cout << "a gpio changed!" << std::endl;});
    gpios.init();
    
    gpios.set_output(GPIO_PIN::OUT1, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    gpios.set_output(GPIO_PIN::OUT1, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    gpios.set_output(GPIO_PIN::OUT1, 0);


    // wait for input to exit the program...
    std::atomic<bool> stop;
    std::thread t([&stop](){while(!stop){};});
    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();
    stop = true;
    t.join();
    
    return 0;
}