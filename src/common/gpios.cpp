#include "gpios.h"
#define Error(fmt, ...) \
    fprintf(stderr, "Error: " fmt "\nFile: %s\nLine: %d\n", ##__VA_ARGS__, __FILE__, __LINE__)
#define Warning(fmt, ...) \
    fprintf(stderr, "Warning: " fmt "\nFile: %s\nLine: %d\n", ##__VA_ARGS__, __FILE__, __LINE__)

bool GPIOS::init()
{
    // openning chipgpio0 and 1
    for (int i = 0; i < 2; i++)
    {
        auto chip = gpiod_chip_open_by_name(("gpiochip" + std::to_string(i)).c_str());
        if (!chip)
        {
            Error("Open chip %d failed.", i);
            return false;
        }
        _chips.push_back(chip);
    }

    for (const auto &[key, gpio] : GPIOPINS)
    {
        auto line = gpiod_chip_get_line(_chips.at(gpio->chip_num), gpio->line_num);
        if (!line)
        {
            Error("Open line %d on chip %d for %s failed.", gpio->line_num, gpio->chip_num, gpio->picus_name.c_str());
            return false;
        }
        _gpios.emplace(key, new GPIOData(line));

        // set as a output pin
        if (gpio->direction == OUTPUT)
        {

            auto ret = gpiod_line_request_output(line, gpio->pin_name.c_str(), 0);
            if (ret < 0)
            {
                Error("Request line as output for %s failed", gpio->picus_name.c_str());
                return false;
            }
            continue; // thats it for output lines!
        }

        // set as a input pin
        auto ret = gpiod_line_request_both_edges_events(line, gpio->pin_name.c_str());
        if (ret < 0)
        {
            Error("Request event notification for %s failed", gpio->picus_name.c_str());
            return false;
        }

        struct timespec ts = {1, 0};
        _input_monitor_threads.push_back(std::thread{
            [=]() -> void
            {
                struct gpiod_line_event event;

                while (true)
                {

                    auto ret = gpiod_line_event_wait(line, &ts);
                    if (ret < 0)
                    {
                        Warning("Wait event notification failed\n");
                        continue;
                    }
                    else if (ret == 0)
                    {
                        continue;
                    }
                    auto value = gpiod_line_get_value(line);
                    ret = gpiod_line_event_read(line, &event);

                    _gpios[key]->state = (1 - value); // lets invert the value. because it is active low
                    gpioChanged();
                };
            }});
    }

    return true;
}

bool GPIOS::set_output(GPIO_PIN pin, int state)
{
    if (!_gpios.count(pin))
    {
        Error("couldn't find configuration gpio %s", GPIOS.at(pin)->picus_name.c_str());
        return;
    }

    if (state == 1 || state == 0)
    {
        auto ret = gpiod_line_set_value(_gpios.at(pin)->line, state);
        gpioChanged();
    }
}