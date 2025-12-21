#include "rfid_manager.h"

RFIDManager::RFIDManager(uint8_t ss, uint8_t rst)
    : pinSS(ss), pinRST(rst) {}

void RFIDManager::begin()
{
    SPI.begin();
    rfid.PCD_Init(pinSS, pinRST);
}

bool RFIDManager::scan(String &uid)
{
    if (!rfid.PICC_IsNewCardPresent())
        return false;
    if (!rfid.PICC_ReadCardSerial())
        return false;

    uid = "";
    for (byte i = 0; i < rfid.uid.size; i++)
        uid += String(rfid.uid.uidByte[i], HEX);
    uid.toUpperCase();

    return true;
}
