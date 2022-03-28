#include "config.h"
#include "Button2.h"
 
uint time_count = 0;
Led led(LED_PIN);
Button2 btn1, btn2;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    udpSetup();
    // tcpSetup();
    IMUsetup();
    delay(500);
    led.ledOn();
    btn1.begin(KEY1_PIN);
    btn2.begin(KEY2_PIN);
    btn1.setClickHandler(onBtn1Click);
}

void loop()
{
    if (mpu.update()) {
        debugData[CH_ACCX] = mpu.getAccX();
        debugData[CH_ACCY] = mpu.getAccY();
        debugData[CH_ACCZ] = mpu.getAccZ();
        debugData[CH_GYRX] = mpu.getGyroX();
        debugData[CH_GYRY] = mpu.getGyroY();
        debugData[CH_GYRZ] = mpu.getGyroZ();
        if (time_count % 100 == 0) {
            print_acc_gyro();
            print_roll_pitch_yaw();
            print_quaternion();
            led.ledTurn();
        }
        // tcpSendData();
        udpSendData();
    }
    
    if (time_count % 1000 == 0) {
        printIP();
    }

    btn1.loop();
    btn2.loop();

    delay(20);
    time_count++;
}
