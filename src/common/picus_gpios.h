#ifndef _PICUS_GPIOS_H
#define _PICUS_GPIOS_H

#include <string>
#include <vector>
#include <map>

enum GPIO_PIN
{
    IN1,
    IN2,
    IN3,
    IN4,
    OUT1,
    OUT2,
    OUT3,
    OUT4
};

enum GPIO_DIR
{
    INPUT,
    OUTPUT
};

struct PicusGpioType
{
    std::string pin_name;
    std::string picus_name;
    int chip_num;
    int line_num;
    GPIO_DIR direction;

    PicusGpioType(const std::string &pin_name, const std::string &picus_name, int chip, int line, GPIO_DIR dir)
        : pin_name(pin_name), picus_name(picus_name), chip_num(chip), line_num(line), direction(dir) {};
};

struct GPIOData
{
    struct gpiod_line *line;
    int state = 0;
    GPIOData(gpiod_line *line) : line(line) {};
};

static const std::map<GPIO_PIN, PicusGpioType *> GPIOPINS = {
    {IN1, new PicusGpioType("PCC.03", "IN1", 1, 15, INPUT)},
    {IN2, new PicusGpioType("PCC.02", "IN2", 1, 14, INPUT)},
    {IN3, new PicusGpioType("PCC.00", "IN3", 1, 12, INPUT)},
    {IN4, new PicusGpioType("PP.06", "IN4", 0, 98, INPUT)},
    {OUT1, new PicusGpioType("PH.00", "OUT1", 0, 43, OUTPUT)},
    {OUT2, new PicusGpioType("PN.01", "OUT2", 0, 85, OUTPUT)},
    {OUT3, new PicusGpioType("PQ.06	", "OUT3", 0, 106, OUTPUT)},
    {OUT4, new PicusGpioType("PEE.02", "OUT4", 1, 25, OUTPUT)}};

#endif