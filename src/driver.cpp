#include "driver.h"

// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_B     4

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13 //0 ~ 2^13-1=8191

// use 5000 Hz as a LEDC base frequency
#define SERVO_BASE_FREQ         50
#define BRUSHLESS_BASE_FREQ     250

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define SERVO_PIN_1     33
#define SERVO_PIN_2     25
#define SERVO_PIN_3     26
#define SERVO_PIN_4     27

#define BRUSHLESS_PIN   12

const uint8_t servo_ch[4] = {0, 1, 2, 3};
const float period = 1000 / BRUSHLESS_BASE_FREQ;
const float lowDuty = 1.0 * 8192 / period;
const float highDuty = 2.0 * 8192 / period;
const float dutyWidth = highDuty - lowDuty;

void PWMSetup()
{
    ledcSetup(servo_ch[0], SERVO_BASE_FREQ, LEDC_TIMER_13_BIT);
    ledcAttachPin(SERVO_PIN_1, servo_ch[0]);
    ledcSetup(servo_ch[1], SERVO_BASE_FREQ, LEDC_TIMER_13_BIT);
    ledcAttachPin(SERVO_PIN_2, servo_ch[1]);
    ledcSetup(servo_ch[2], SERVO_BASE_FREQ, LEDC_TIMER_13_BIT);
    ledcAttachPin(SERVO_PIN_3, servo_ch[2]);
    ledcSetup(servo_ch[3], SERVO_BASE_FREQ, LEDC_TIMER_13_BIT);
    ledcAttachPin(SERVO_PIN_4, servo_ch[3]);

    ledcSetup(LEDC_CHANNEL_B, BRUSHLESS_BASE_FREQ, LEDC_TIMER_13_BIT);//1-2ms duty:40-80
    ledcAttachPin(BRUSHLESS_PIN, LEDC_CHANNEL_B);
    setBrushless(0);
    setServo(1, 500);
    setServo(2, 500);
    setServo(3, 500);
    setServo(4, 500);
}

// Arduino like analogWrite
// value has to be between 0 and 1000

void setBrushless(int32_t value) 
{
    // calculate duty, 8191 from 2 ^ 13 - 1
    value = value > 1000 ? 1000 : value;
    value = value < 0 ? 0 : value;
    uint32_t duty = lowDuty + value * dutyWidth / 1000;
    // write duty to LEDC
    ledcWrite(LEDC_CHANNEL_B, duty);
}

// ch between 1-4
// value has to be between 0 and 1000
void setServo(uint8_t ch, int32_t value) 
{
    // calculate duty, 8191 from 2 ^ 13 - 1
    value = value > 1000 ? 1000 : value;
    value = value < 0 ? 0 : value;
    uint32_t duty = 205 + (value * 819) / 1000;
    // write duty to LEDC
    if (ch > 4 || ch < 1)
    {
        return;
    }
    ledcWrite(servo_ch[ch-1], duty);
}