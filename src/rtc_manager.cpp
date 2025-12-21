#include <Arduino.h>
#include "rtc_manager.h"

bool RTCManager::begin()
{
    if (!rtc.begin())
    {
        Serial.println("RTC not found!");
        ready = false;
        return false;
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, set manually!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    ready = true;
    return true;
}

bool RTCManager::isRunning()
{
    return ready;
}

DateTime RTCManager::now()
{
    if (!ready)
        return DateTime(2000, 1, 1, 0, 0, 0);
    return rtc.now();
}

String RTCManager::nowTimestamp()
{
    if (!ready)
        return "NO_RTC";

    DateTime t = rtc.now();
    char buf[25];
    snprintf(buf, sizeof(buf),
             "%04d-%02d-%02d %02d:%02d:%02d",
             t.year(), t.month(), t.day(),
             t.hour(), t.minute(), t.second());

    return String(buf);
}
