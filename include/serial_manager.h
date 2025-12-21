#pragma once
#include "user_db.h"
#include "rfid_manager.h"
#include "config_manager.h"

class SerialManager
{
public:
    SerialManager(ConfigManager &config, RFIDManager &rfid, UserDatabase &userdb);
    void begin(uint32_t baud = 115200);
    void loop();

private:
    ConfigManager &config;
    RFIDManager &rfid;
    UserDatabase &userdb;

    unsigned long lastTimeout;
    const unsigned long timeoutInterval = 10000; // 10 detik

    void handleCommand(String cmd);
    void printHelp();
    bool readName(String &name);
};