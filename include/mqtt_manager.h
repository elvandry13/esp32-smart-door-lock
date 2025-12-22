#pragma once
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "wifi_manager.h"
#include "config_manager.h"
#include "rtc_manager.h"

class MqttManager
{
public:
    MqttManager(
        WiFiManager &wifi,
        ConfigManager &config,
        RTCManager &rtc);

    void begin();
    void loop();

    void publish(String uid, String name);
    bool isConnected();
    String getClientID();

private:
    WiFiManager &wifi;
    ConfigManager &config;
    RTCManager &rtc;

    WiFiClient espClient;
    PubSubClient mqtt;

    unsigned long lastReconnect = 0;
    const unsigned long reconnectInterval = 3000;

    void reconnect();
    void onMessage(char *topic, byte *payload, unsigned int length);
    String clientID();
};
