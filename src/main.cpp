#include "config.h"
 
uint time_count = 0;
Led led(LED_PIN);
Key key1(KEY1_PIN);
Key key2(KEY2_PIN);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    udpSetup();
    // tcpSetup();
    IMUsetup();
    delay(200);
    led.ledOn();
    
}

void loop()
{
    if (mpu.update()) {
        // print_quaternion();
        debugData[CH_ACCX] = mpu.getAccX();
        debugData[CH_ACCY] = mpu.getAccY();
        debugData[CH_ACCZ] = mpu.getAccZ();
        debugData[CH_GYRX] = mpu.getGyroX();
        debugData[CH_GYRY] = mpu.getGyroY();
        debugData[CH_GYRZ] = mpu.getGyroZ();

        // tcpSendData();
        udpSendData();
    }
    if (time_count % 100 == 0) {
        print_roll_pitch_yaw();
        led.ledTurn();
    }
    if (time_count % 1000 == 0) {
        printIP();
    }
    delay(20);
    time_count++;
}
