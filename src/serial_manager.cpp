#include "serial_manager.h"

SerialManager::SerialManager(
    ConfigManager &c,
    RFIDManager &r,
    UserDatabase &u) : config(c), rfid(r), userdb(u) {}

void SerialManager::begin(uint32_t baud)
{
    Serial.begin(baud);
    delay(200);
    printHelp();
}

void SerialManager::loop()
{
    if (!Serial.available())
        return;

    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.length() == 0)
        return;

    handleCommand(cmd);
}

bool SerialManager::readName(String &name)
{
    name = "";

    if (!Serial.available())
        return false;

    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.length() == 0)
        return false;
    
    name = cmd;
    return true;
}

void SerialManager::handleCommand(String cmd)
{
    auto &cfg = config.get();

    // ===== WIFI =====
    if (cmd.startsWith("wifi "))
    {
        int p = cmd.indexOf(' ', 5);
        if (p < 0)
            return;

        cfg.wifi_ssid = cmd.substring(5, p);
        cfg.wifi_pass = cmd.substring(p + 1);
        Serial.println("OK: WiFi updated");
    }

    // ===== MQTT =====
    else if (cmd.startsWith("mqtt "))
    {
        // mqtt host port user pass
        int p1 = cmd.indexOf(' ', 5);
        int p2 = cmd.indexOf(' ', p1 + 1);
        int p3 = cmd.indexOf(' ', p2 + 1);

        if (p3 < 0)
            return;

        cfg.mqtt_host = cmd.substring(5, p1);
        cfg.mqtt_port = cmd.substring(p1 + 1, p2).toInt();

        Serial.println("OK: MQTT updated");
    }

    // ===== REGISTER =====
    else if (cmd.startsWith("register "))
    {
        String inputName = cmd.substring(9);
        String uid;

        lastTimeout = millis();
        Serial.print("Silakan scan tag : ");
        while (!rfid.scan(uid))
        {
            if (millis() - lastTimeout >= timeoutInterval)
            {
                Serial.println("Timeout");
                return;
            }
            delay(10);
        }
        Serial.println(uid);

        if (userdb.add(uid, inputName))
            Serial.println("OK: UID & Name registered");
        else
            Serial.println("UID sudah ada");
    }

    // ===== DELETE =====
    else if (cmd.startsWith("delete"))
    {
        String uid;
        lastTimeout = millis();
        Serial.print("Silakan scan tag : ");
        while (!rfid.scan(uid))
        {
            if (millis() - lastTimeout >= timeoutInterval)
            {
                Serial.println("Timeout");
                return;
            }
            delay(10);
        }
        Serial.println(uid);

        if (userdb.remove(uid))
            Serial.println("OK: User dihapus");
        else
            Serial.println("UID tidak ada");
    }

    // ===== SHOW =====
    else if (cmd == "show")
    {
        Serial.println("===== CURRENT CONFIG =====");
        Serial.println("SSID     : " + cfg.wifi_ssid);
        Serial.println("PASS     : " + cfg.wifi_pass);
        Serial.println("MQTT     : " + cfg.mqtt_host + ":" + String(cfg.mqtt_port));
    }

    else if (cmd == "save")
    {
        config.saveConfig();
        Serial.println("OK: Config saved. Restarting...");
        delay(3000);
        ESP.restart();
    }

    else if (cmd == "help")
    {
        printHelp();
    }

    else
    {
        Serial.println("Unknown command. Type: help");
    }
}

void SerialManager::printHelp()
{
    Serial.println();
    Serial.println("===== SERIAL CONFIG =====");
    Serial.println("wifi <ssid> <pass>");
    Serial.println("mqtt <host> <port>");
    Serial.println("register");
    Serial.println("delete");
    Serial.println("show");
    Serial.println("save");
    Serial.println("help");
    Serial.println("=========================");
}
