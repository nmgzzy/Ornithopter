#include "config.h"

Led led(LED_PIN);
uint count = 0;

void setup()
{
    delay(100);
    Serial.begin(115200);
    PWMSetup();
    delay(300);
    // readEEPROM();
    BLEsetup();
    IMUsetup();
    receiverSetup();
    Serial.println("setup Success");
    delay(200);
}

void loop()
{
    count++;
    control();
    led.blink();
    BLEloop();




    delay(5);
}
