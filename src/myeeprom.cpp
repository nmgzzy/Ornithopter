#include "EEPROM.h"
#include "myeeprom.h"
#include <ArduinoJson.h>

uint16_t parsize = 600;

void readEEPROM()
{
    EEPROM.begin(parsize);
    String s = EEPROM.readString(0);
    EEPROM.end();
    json2par(s.c_str());
}

void writeEEPROM()
{
    EEPROM.begin(parsize);
    char s[parsize];
    par2json(s, parsize);
    EEPROM.writeString(0, String(s));
    if (!EEPROM.commit()) {
        Serial.println("parameter write error!");
    }
    EEPROM.end();
    Serial.print(s);
}

void json2par(const char* json)
{
    DynamicJsonDocument doc(parsize);
    deserializeJson(doc, json);
    pitchPID.Kp=doc["pp"];
    pitchPID.Ki=doc["pi"];
    pitchPID.Kd = doc["pd"];
    pitchPID.integLimit = doc["pil"];
    pitchPID.outputUpLimit = doc["poul"];
    pitchPID.outputDownLimit = doc["podl"];
    rollPID.Kp = doc["rp"];
    rollPID.Ki = doc["ri"];
    rollPID.Kd = doc["rpd"];
    rollPID.integLimit = doc["ril"];
    rollPID.outputUpLimit = doc["roul"];
    rollPID.outputDownLimit = doc["rodl"];
    yawPID.Kp = doc["yp"];
    yawPID.Ki = doc["yi"];
    yawPID.Kd = doc["yd"];
    yawPID.integLimit = doc["yil"];
    yawPID.outputUpLimit = doc["youl"];
    yawPID.outputDownLimit = doc["yodl"];
    ssid = String((const char *)doc["ssid"]);
    password = String((const char *)doc["pswd"]);
    udpHost = IPAddress();
    udpHost.fromString((const char *)doc["host"]);
    udpPort = doc["port"];
}

void par2json(char* json, uint16_t len)
{
    // 'pp': 1, 'pi': 0.2, 'pd': 3.5, 'pil': 100, 'poul': 1000, 'podl': 0,
    // 'rp': 1, 'ri': 0.2, 'rd': 3.5, 'ril': 100, 'roul': 1000, 'rodl': 0,
    // 'yp': 1, 'yi': 0.2, 'yd': 3.5, 'yil': 100, 'youl': 1000, 'yodl': 0,
    DynamicJsonDocument doc(parsize);

    doc["pp"] = pitchPID.Kp;
    doc["pi"] = pitchPID.Ki;
    doc["pd"] = pitchPID.Kd;
    doc["pil"] = pitchPID.integLimit;
    doc["poul"] = pitchPID.outputUpLimit;
    doc["podl"] = pitchPID.outputDownLimit;
    doc["rp"] = rollPID.Kp;
    doc["ri"] = rollPID.Ki;
    doc["rpd"] = rollPID.Kd;
    doc["ril"] = rollPID.integLimit;
    doc["roul"] = rollPID.outputUpLimit;
    doc["rodl"] = rollPID.outputDownLimit;
    doc["yp"] = yawPID.Kp;
    doc["yi"] = yawPID.Ki;
    doc["yd"] = yawPID.Kd;
    doc["yil"] = yawPID.integLimit;
    doc["youl"] = yawPID.outputUpLimit;
    doc["yodl"] = yawPID.outputDownLimit;
    doc["ssid"] = ssid.c_str();
    doc["pswd"] = password.c_str();
    doc["host"] = udpHost.toString().c_str();
    doc["port"] = udpPort;

    serializeJson(doc, json, len);
}
