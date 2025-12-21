#pragma once
#include <MFRC522.h>
#include <SPI.h>

class RFIDManager
{
public:
    RFIDManager(uint8_t ss, uint8_t rst);
    void begin();
    bool scan(String &uid);

private:
    uint8_t pinSS, pinRST;
    MFRC522 rfid;
};
