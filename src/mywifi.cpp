#include <WiFi.h>
#include <WiFiUdp.h>
#include "mywifi.h"

// const char* ssid = "LENOVO-XIN";
// const char* password =  "babababa";
// const char * host = "192.168.137.1";

const char* ssid = "ZZZ-2.4G";
const char* password =  "so171tf1";
const char * host = "10.0.0.16";
const uint16_t port = 1347;
const uint16_t udpPort = 1346;
boolean connected = false;
WiFiUDP udp;

float debugData[DEBUGCHANNLE] = {0};
uint8_t sendSize[] = {0, CN_NUM_DATA, CN_NUM_PAR, CN_NUM_POSE};
uint8_t sendMode = CN_NUM_POSE;

void tcpSetup()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());
}

//justfloat
void tcpSendData()
{
    WiFiClient client;
    debugData[0] = sendMode;
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        return;
    }
    if(sendMode < sizeof(sendSize) / sizeof(sendSize[0])) {
        client.write((uint8_t *)debugData, sendSize[sendMode]*sizeof(float));
    }
    client.stop();
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

int tcpReceiveData()
{
    String a = "name:123\n";
    // while(client.available()) {
    //     String line = client.readStringUntil('\r');
    //     Serial.print(line);
    // }

    return 0;
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            //When connected set 
            Serial.print("WiFi connected! IP address: ");
            Serial.println(WiFi.localIP());  
            //initializes the UDP state
            //This initializes the transfer buffer
            udp.begin(WiFi.localIP(),udpPort);
            connected = true;
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("WiFi lost connection");
            connected = false;
            break;
        default: break;
    }
}

void connectToWiFi(const char * ssid, const char * pwd){
    Serial.println("Connecting to WiFi network: " + String(ssid));

    // delete old config
    WiFi.disconnect(true);
    //register event handler
    WiFi.onEvent(WiFiEvent);

    //Initiate connection
    WiFi.begin(ssid, pwd);

    Serial.println("Waiting for WIFI connection...");
}

void udpSetup(){
    //Connect to the WiFi network
    connectToWiFi(ssid, password);
}

//justfloat
void udpSendData(){
    //only send data when connected
    if(connected) {
        //Send a packet
        debugData[0] = sendMode;
        udp.beginPacket(host,udpPort);
        if(sendMode < sizeof(sendSize) / sizeof(sendSize[0])) {
            // udp.write((uint8_t *)debugData, sendSize[sendMode]*sizeof(float));
            udp.print("12345");
        }
        udp.endPacket();
    }
    else {
        Serial.println("udp send error");
    }
}

int udpReceiveData()
{

    return 0;
}

void printIP()
{
    Serial.println(WiFi.localIP());
}