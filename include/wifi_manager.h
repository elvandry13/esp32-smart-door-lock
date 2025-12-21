#pragma once
#include <WiFi.h>
#include "config_manager.h"

class WiFiManager
{
public:
	WiFiManager(ConfigManager &cfg);

	void begin();
	void loop();

	bool isConnected() const;
	String getIP() const;

private:
	ConfigManager &config;
	unsigned long lastReconnect = 0;
	const unsigned long reconnectInterval = 10000; // 10 detik

	void connect();
};
