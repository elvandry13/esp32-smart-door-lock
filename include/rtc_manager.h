#pragma once
#include <RTClib.h>

class RTCManager
{
public:
    bool begin();
    DateTime now();
    bool isRunning();
    String nowTimestamp();

private:
    RTC_DS3231 rtc;
    bool ready = false;
};
