# ESP32 Smart Door Lock

ESP32 Smart Door Lock adalah sistem pengunci pintu pintar berbasis RFID, menggunakan ESP32 sebagai controller utama. LCD 16x2 sebagai antarmuka, RTC DS3231 sebagai komponen untuk mendapatkan data waktu, serta Relay dan soldenoid door lock 12V sebagai mekanikal kunci pintu. Data logging dikirim menggunakan protokol MQTT. Notifikasi kunci pintu menggunakan bot Telegram.

---

## Fitur Utama

- Registrasi kartu RFID + nama pengguna
- Validasi akses pintu
- Notifikasi Telegram
- Log akses + timestamp
- Penyimpanan internal ESP32 (NVS)
- LCD 16x2 sebagai antarmuka lokal
- Arsitektur modular berbasis class

---

## Hardware yang Dibutuhkan

- ESP32 Dev Module
- RFID MFRC522
- LCD I2C 16x2
- RTC DS3231
- Relay module
- Solenoid door lock

---

## Library yang Digunakan

- `ESP32 Arduino Framework`
- `ArduinoJson`
- `PubSubClient (MQTT)`
- `LiquidCrystal_I2C`
- `UniversalTelegramBot`
- `Preferences (NVS)`

Pastikan semua library sudah terinstall di Arduino IDE.

---

## MQTT Topic & Payload

### Topic Publish

```bash
<clientID>/doorlock
```

### Contoh Payload Publish

```json
{
    "device_id":"smartdoorlock_98A7B4962BC8",
    "nama":"Elvandry",
    "uid":"936A335",
    "waktu":"2025-12-21 20:44:05"
}
```

---

## Konfigurasi via Serial Monitor

Gunakan **baudrate 115200** dan kirim perintah berikut:

### Set WiFi

```bash
wifi <NamaWifi> <PasswordWifi>
```

### Set MQTT

```bash
mqtt <Host> <Port>
```

### Register User

```bash
register <nama>
```

### Delete User

```bash
delete
```

### Simpan Konfigurasi

```bash
save
```

ESP32 akan restart dan menggunakan konfigurasi baru.

### Cek Config

```bash
show
```

---

## Keamanan Credential

Project ini menggunakan file terpisah:

```bash
credentials.h
```

**Jangan upload file ini ke GitHub.**
Tambahkan ke `.gitignore`:

```bash
credentials.h
```

### Contoh `credentials_example.h`

```cpp
#define WIFI_SSID     "nama_wifi"
#define WIFI_PASSWORD "password_wifi"

#define MQTT_BROKER   "broker.hivemq.com"
#define MQTT_PORT     1883
```

---

## Lisensi

Project ini bersifat **open-source** dan bebas digunakan untuk pembelajaran dan pengembangan pribadi.

---

## Kontributor

Dikembangkan untuk project IoT & pembelajaran embedded systems berbasis ESP32.
