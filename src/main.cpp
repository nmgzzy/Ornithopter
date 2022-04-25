#include "config.h"
#include "Button2.h"
 
Led led(LED_PIN);
Button2 btn1, btn2;

void setup()
{
    delay(200);
    Serial.begin(115200);
    delay(200);
    //udpSetup();
    delay(200);
    //IMUsetup();
    delay(200);
    led.ledOn();
    btn1.begin(KEY1_PIN);
    btn2.begin(KEY2_PIN);
    btn1.setClickHandler(onBtn1Click);
    btn2.setClickHandler(onBtn2Click);
    receiverSetup();
    //PWMSetup();
    delay(200);
    //timerSetup();
}

void loop()
{
    // if (mpu.update()) {
    //     // debugData[CH_W]    = mpu.getQuaternionW();
    //     debugData[CH_X]    = mpu.getEulerX();
    //     debugData[CH_Y]    = mpu.getEulerY();
    //     debugData[CH_Z]    = mpu.getEulerZ();
    //     debugData[CH_ACCX] = mpu.getAccX();
    //     debugData[CH_ACCY] = mpu.getAccY();
    //     debugData[CH_ACCZ] = mpu.getAccZ();
    //     debugData[CH_GYRX] = mpu.getGyroX();
    //     debugData[CH_GYRY] = mpu.getGyroY();
    //     debugData[CH_GYRZ] = mpu.getGyroZ();
    //     if (time_count % 5 == 0) {
    //         // print_acc_gyro();
    //         // print_roll_pitch_yaw();
    //         // print_quaternion();
    //         led.ledTurn();
    //         udpSendData();
    //     }
    // }
    if (time_count % 25 == 0) {
        led.ledTurn();
    }
    btn1.loop();
    btn2.loop();
    receiverLoop();
    // Serial.printf("%d  %d\n", time_count, cnt);
    delay(10);
}
