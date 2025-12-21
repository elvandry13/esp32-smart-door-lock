#include "user_db.h"

void UserDatabase::begin()
{
    prefsDb.begin("users", false);
}

bool UserDatabase::find(String uid, String &name)
{
    JsonDocument doc;
    deserializeJson(doc, prefsDb.getString("db", "[]"));

    for (JsonObject u : doc.as<JsonArray>())
    {
        if (u["uid"] == uid)
        {
            name = u["name"].as<String>();
            return true;
        }
    }
    return false;
}

bool UserDatabase::add(String uid, String name)
{
    JsonDocument doc;
    deserializeJson(doc, prefsDb.getString("db", "[]"));

    for (JsonObject u : doc.as<JsonArray>())
        if (u["uid"] == uid)
            return false;

    JsonObject obj = doc.as<JsonArray>().createNestedObject();
    obj["uid"] = uid;
    obj["name"] = name;

    String out;
    serializeJson(doc, out);
    prefsDb.putString("db", out);
    return true;
}

bool UserDatabase::remove(String uid)
{
    JsonDocument doc;
    deserializeJson(doc, prefsDb.getString("db", "[]"));

    JsonArray arr = doc.as<JsonArray>();
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i]["uid"] == uid)
        {
            arr.remove(i);
            String out;
            serializeJson(doc, out);
            prefsDb.putString("db", out);
            return true;
        }
    }
    return false;
}
