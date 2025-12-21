#pragma once
#include <Preferences.h>
#include <ArduinoJson.h>

class UserDatabase
{
public:
    void begin();
    bool find(String uid, String &name);
    bool add(String uid, String name);
    bool remove(String uid);
    
private:
    Preferences prefsDb;
};
