#include "board_config.h"
#include "config_manager.h"
#include "display_manager.h"
#include "relay_controller.h"
#include "rfid_manager.h"
#include "serial_manager.h"
#include "user_db.h"
#include "rtc_manager.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "telegram_notifier.h"
#include "credentials.h"

ConfigManager config;
DisplayManager display;
RelayController door(PIN_RELAY);
RFIDManager rfid(PIN_SS, PIN_RST);
UserDatabase userdb;
SerialManager ser(config, rfid, userdb);
RTCManager rtc;
WiFiManager wifi(config);
MqttManager mqtt(wifi, config, rtc);
TelegramNotifier telegram(BOT_TOKEN, ADMIN_CHAT_ID);

void setup()
{
	config.loadConfig();
	display.begin();
	door.begin();
	rfid.begin();
	userdb.begin();
	ser.begin();
	rtc.begin();
	wifi.begin();
	mqtt.begin();
	telegram.begin();
	display.show("Silakan scan", "kartu / tag");
	Serial.println("ClientID : " + mqtt.getClientID());
}

void loop()
{
	ser.loop();
	wifi.loop();
	mqtt.loop();
	
	String uid, name;
	if (rfid.scan(uid))
	{
		if (userdb.find(uid, name))
		{
			display.show("Akses OK", name);
			door.unlock();
			mqtt.publish(uid, name);
			telegram.send(uid, name);
		}
		else
		{
			display.show("Akses ditolak", "");
			delay(2000);
		}
		display.show("Silakan scan", "kartu / tag");
	}
}
