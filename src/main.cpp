#include "config.h"
 
Led led(LED_PIN);
uint count = 0;
uint8_t SystemMode = 0; //0-debug; 1-safe mode; 2-run;

void setup()
{
    delay(200);
    Serial.begin(115200);
    delay(300);
    BtnSetup();
    readEEPROM();
    BtnSetup();
    udpSetup();
    IMUsetup();
    receiverSetup();
    PWMSetup();
    Serial.println("setup Success");
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
    
    delay(5);
    if (count % 10 == 0)
    {
        // print_roll_pitch_yaw();
    }
    
}
