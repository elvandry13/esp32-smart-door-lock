#include "push_button.h"

PushButton::PushButton(uint8_t pb)
    : buttonPin(pb) {}

void PushButton::begin()
{
    pinMode(buttonPin, INPUT_PULLUP);
}

bool PushButton::isPressed()
{
    return !digitalRead(buttonPin);
}
