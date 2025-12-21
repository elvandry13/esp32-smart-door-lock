#pragma once
#include <LiquidCrystal_I2C.h>

class DisplayManager
{
public:
    DisplayManager();
    void begin();
    void show(String l1, String l2);

private:
    LiquidCrystal_I2C lcd;
};
