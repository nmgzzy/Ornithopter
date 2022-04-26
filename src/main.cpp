#include "config.h"
 
Led led(LED_PIN);
uint count = 0;
uint8_t SystemMode = 0; //0-debug; 1-safe mode; 2-run;

void setup()
{
    delay(300);
    Serial.begin(115200);
    // readEEPROM();
    BtnSetup();
    udpSetup();
    IMUsetup();
    receiverSetup();
    PWMSetup();
    delay(200);
}

void loop()
{
    count++;
    control();
    btn1.loop();
    btn2.loop();
    led.blink();
    //wifi
    delay(1);
}
