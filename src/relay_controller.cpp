#include "relay_controller.h"

RelayController::RelayController(uint8_t rel)
    : relayPin(rel) {}

void RelayController::begin()
{
    pinMode(relayPin, OUTPUT);
}

void RelayController::unlock()
{
    digitalWrite(relayPin, HIGH);
    delay(3000);
    digitalWrite(relayPin, LOW);
}
