#pragma once
#include <Arduino.h>

class RelayController
{
public:
    RelayController(uint8_t rel);
    void begin();
    void unlock();

private:
    uint8_t relayPin;
};
