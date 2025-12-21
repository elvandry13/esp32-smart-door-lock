#include "wifi_manager.h"

WiFiManager::WiFiManager(ConfigManager &cfg)
    : config(cfg) {}

void WiFiManager::begin()
{
    WiFi.mode(WIFI_STA);
    connect();
}

void WiFiManager::connect()
{
    auto &cfg = config.get();

    if (cfg.wifi_ssid.isEmpty())
    {
        Serial.println("WiFi SSID belum dikonfigurasi");
        return;
    }

    Serial.print("Connecting to WiFi: ");
    Serial.println(cfg.wifi_ssid);

    WiFi.begin(cfg.wifi_ssid.c_str(), cfg.wifi_pass.c_str());
}

void WiFiManager::loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        unsigned long now = millis();
        if (now - lastReconnect > reconnectInterval)
        {
            lastReconnect = now;
            Serial.println("WiFi disconnected, reconnecting...");
            connect();
        }
    }
}

bool WiFiManager::isConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getIP() const
{
    if (isConnected())
    {
        return WiFi.localIP().toString();
    }
    return "-";
}
