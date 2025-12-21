#pragma once
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TelegramNotifier
{
public:
    TelegramNotifier(const String &token, const String &chatId);
    void begin();
    void send(String uid, String name);

private:
    String botToken;
    String chatID;
    WiFiClientSecure client;
    UniversalTelegramBot bot;
};
