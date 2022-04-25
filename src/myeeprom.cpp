/*
  ESP32 eeprom_class example with EEPROM library
  This simple example demonstrates using EEPROM library to store different data in
  ESP32 Flash memory in a multiple user-defined EEPROM class objects.

  Created for arduino-esp32 on 25 Dec, 2017
  by Elochukwu Ifediora (fedy0)
  converted to nvs by lbernstone - 06/22/2019
*/

#include "EEPROM.h"
#include "myeeprom.h"
#include <ArduinoJson.h>
#include "mytimer.h"

uint16_t parsize = 600;

void readEEPROM()
{
    EEPROM.begin(parsize);
    String s = EEPROM.readString(0);
    json2par(s.c_str());
    EEPROM.end();
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

    serializeJson(doc, json, len);
}
