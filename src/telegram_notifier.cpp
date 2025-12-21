#include "telegram_notifier.h"

TelegramNotifier::TelegramNotifier(const String &token, const String &chatId)
    : botToken(token),
      chatID(chatId),
      bot(token, client) {}

void TelegramNotifier::begin()
{
    client.setInsecure();
}

void TelegramNotifier::send(String uid, String name)
{
    String msg = "🔓 SMART DOOR LOCK\n";
    msg += "Nama : " + name + "\n";
    msg += "UID  : " + uid + "\n";
    msg += "telah membuka kunci pintu!";

    bot.sendMessage(chatID, msg, "");
}
