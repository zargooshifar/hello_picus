#ifndef _GPIOS_H
#define _GPIOS_H
#include <gpiod.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include "picus_gpios.h"
#include <functional>

class GPIOS
{
public:
    GPIOS() {}

    bool init();
    bool set_output(GPIO_PIN pin, int state);

    void setGPIOCallback(std::function<void()> gpioChanged);

private:
    struct GPIOData
    {
        struct gpiod_line *line;
        int state = 0;
        GPIOData(gpiod_line *line) : line(line) {};
    };

    std::map<GPIO_PIN, GPIOData *> _gpios;
    std::vector<gpiod_chip *> _chips;
    std::vector<std::thread> _input_monitor_threads;

    std::function<void()> _gpioChanged;
};
#endif