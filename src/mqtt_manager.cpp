#include "mqtt_manager.h"

MqttManager::MqttManager(
    WiFiManager &w,
    ConfigManager &c,
    RTCManager &t) : wifi(w), config(c), time(t), mqtt(espClient) {}

void MqttManager::begin()
{
    auto &cfg = config.get();
    mqtt.setServer(cfg.mqtt_host.c_str(), cfg.mqtt_port);
}

String MqttManager::clientID()
{
    uint64_t mac = ESP.getEfuseMac();
    char id[32];
    sprintf(id, "smartdoorlock_%04X%08X",
            (uint16_t)(mac >> 32),
            (uint32_t)mac);
    return String(id);
}

String MqttManager::getClientID()
{
    return clientID();
}

void MqttManager::reconnect()
{
    if (!wifi.isConnected())
        return;

    unsigned long now = millis();
    if (now - lastReconnect < reconnectInterval)
        return;
    lastReconnect = now;

    auto &cfg = config.get();

    Serial.println("Connecting to MQTT...");
    mqtt.connect(clientID().c_str());
    Serial.println("MQTT connected & subscribed");
}

void MqttManager::loop()
{
    if (!mqtt.connected())
    {
        reconnect();
        return;
    }
    mqtt.loop();
}

void MqttManager::publish(String uid, String name)
{
    if (!mqtt.connected())
        return;

    JsonDocument doc;
    doc["device_id"] = clientID();
    doc["nama"] = name;
    doc["uid"] = uid;
    doc["waktu"] = time.nowTimestamp();

    char buffer[256];
    serializeJson(doc, buffer);

    String publishTopic = clientID() + "/doorlock";

    mqtt.publish(publishTopic.c_str(), buffer);
}

bool MqttManager::isConnected()
{
    return mqtt.connected();
}
