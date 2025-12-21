#pragma once
#include <Preferences.h>

struct Config
{
    String wifi_ssid;
    String wifi_pass;
    String mqtt_host;
    uint16_t mqtt_port;
};

class ConfigManager
{
public:
    void loadConfig();
    void saveConfig();

    Config &get();

private:
    Preferences prefsConfig;
    Config cfg;
};
