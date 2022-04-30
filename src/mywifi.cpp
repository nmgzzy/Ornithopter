#include "WiFi.h"
// #include <WiFiUdp.h>
#include "AsyncUDP.h"
#include "mywifi.h"
#include <ArduinoJson.h>

String ssid = String("jmi11");
String password =  String("babababa");
IPAddress udpHost = IPAddress();
uint16_t udpPort = 12345;
boolean connected = false;
AsyncUDP udp;

float debugData[DEBUGCHANNLE] = {0};
uint8_t sendSize[] = {0, CN_NUM_DATA, CN_NUM_PAR, CN_NUM_POSE};
uint8_t sendMode = MODE_POSE;

void udpSetup(){
    //Connect to the WiFi network
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    uint8_t i = 0;
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        i++;
        if (i > 3)
            return;
    }
    if(udp.connect(udpHost, udpPort)) {
        Serial.println("UDP connected");
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.println(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print("Length: ");
            Serial.println(packet.length());
            Serial.print("Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
            udpHost = packet.remoteIP();
            json2par((char *)packet.data());
            writeEEPROM();
        });
        // udp.print("Hello Server! My IP is " + WiFi.localIP().toString());
    }
    udp.listen(udpPort);
    printIP();
}

//justfloat
void udpSendData()
{
    if (!udp.connected()) {
        Serial.println("UDP send Error");
        return;
    }
    debugData[0] = sendMode;
    if(sendMode >= sizeof(sendSize) / sizeof(sendSize[0])) {
        Serial.println("sendMode Error");
        return;
    }
    uint8_t* tmp = (uint8_t *)debugData;
    uint8_t n = sendSize[sendMode]*sizeof(float);
    // add tail
    tmp[n] = 0x00;
    tmp[n+1] = 0x00;
    tmp[n+2] = 0x80;
    tmp[n+3] = 0x7f;
    udp.broadcastTo(tmp, n+4, udpPort);
}

//firewater
void udpSendStrData()
{
    if (!udp.connected()) {
        Serial.println("UDP send Error");
        return;
    }
    debugData[0] = sendMode;
    udp.printf("%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f\n",debugData[1],debugData[2],debugData[3],debugData[4],debugData[5],debugData[6],debugData[7],debugData[8],debugData[9],debugData[10]);
}

bool stringSplit(String src, pair_s &dst) 
{
    int index = -1, end = -1;
    pair_s par;
    for (int i=0; i < src.length(); i++) {
        if (src[i] == ':') {
            index = i;
        }
        if(src[i] == '\n') {
            end = i;
            break;
        }
    }
    if(index == -1 || end == -1) {
        return false;
    }
    par.name = src.substring(0, index);
    par.data.par_f = src.substring(index+1, end).toFloat(); //float?
    dst = par;
    return true;
}

void printIP()
{
    Serial.println(WiFi.localIP());
}