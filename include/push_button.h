#pragma once
#include <Arduino.h>

class PushButton
{
public:
    PushButton(uint8_t pb);
    void begin();
    bool isPressed();

private:
    uint8_t buttonPin;
};
