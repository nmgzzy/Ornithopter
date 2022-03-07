#include <WiFi.h>
#include "mywifi.h"

// const char* ssid = "jmi11";
// const char* password =  "babababa";
const char* ssid = "ZZZ";
const char* password =  "so171tf1";
const uint16_t port = 1347;
const char * host = "192.168.134.93";

float debugData[15] = {0};
const uint8_t nchannel = 1;

void wifiSetup()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
 
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
}

void sendData()
{
    WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
    }
    client.printf("%f\n", debugData[0]);
    client.stop();
}