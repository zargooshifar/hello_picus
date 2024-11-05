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
   
   // set a callback, if any gpio changes you can be notified in this function
    gpios.setGPIOCallback([](std::map<GPIO_PIN, GPIOData*>& gpios) -> void { 
            for (const auto& pair : gpios) {
                std::cout <<  GPIOPINS.at(pair.first)->picus_name.c_str()  << " state is " << pair.second->state << std::endl;
            }
        });
    // initializeing the gpios

    gpios.init();
    

    //settig a output gpio
    gpios.set_output(GPIO_PIN::OUT4, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    gpios.set_output(GPIO_PIN::OUT4, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    gpios.set_output(GPIO_PIN::OUT4, 0);


    // wait for input to exit the program...
    std::atomic<bool> stop;
    std::thread t([&stop](){while(!stop){};});
    std::cout << "Press Enter to exit..." << std::endl;

    std::cin.get();
    stop = true;
    t.join();
    
    return 0;
}