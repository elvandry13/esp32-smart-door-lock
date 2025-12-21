#include "config_manager.h"
#include "credentials.h"

void ConfigManager::loadConfig()
{
	prefsConfig.begin("config", true);
	cfg.wifi_ssid = prefsConfig.getString("wifi_ssid", WIFI_SSID);
	cfg.wifi_pass = prefsConfig.getString("wifi_pass", WIFI_PASS);
	cfg.mqtt_host = prefsConfig.getString("mqtt_host", MQTT_HOST);
	cfg.mqtt_port = prefsConfig.getUInt("mqtt_port", 1883);
	prefsConfig.end();
}

void ConfigManager::saveConfig()
{
	prefsConfig.begin("config", false);
	prefsConfig.putString("wifi_ssid", cfg.wifi_ssid);
	prefsConfig.putString("wifi_pass", cfg.wifi_pass);
	prefsConfig.putString("mqtt_host", cfg.mqtt_host);
	prefsConfig.putUInt("mqtt_port", cfg.mqtt_port);
	prefsConfig.end();
}

Config &ConfigManager::get()
{
	return cfg;
}
