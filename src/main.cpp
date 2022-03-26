#include "config.h"
 
// #define LED_BUILTIN 4
void setup()
{
    Serial.begin(115200);
    //tcpSetup();
    IMUsetup();
    
}

void loop()
{
    if (mpu.update()) {
        print_roll_pitch_yaw();
    }
    delay(100);
}
