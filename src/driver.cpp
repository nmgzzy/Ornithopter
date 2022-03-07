#include "driver.h"

// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_B     4

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13 //0 ~ 2^13-1=8191

// use 5000 Hz as a LEDC base frequency
#define SERVO_BASE_FREQ         50
#define BRUSHLESS_BASE_FREQ     400

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define SERVO_PIN_1     1
#define SERVO_PIN_2     2
#define SERVO_PIN_3     3
#define SERVO_PIN_4     4

#define BRUSHLESS_PIN   5

const uint8_t servo_ch[4] = {0, 1, 2, 3};

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
}

// Arduino like analogWrite
// value has to be between 0 and 1000
void setBrushless(uint32_t value) 
{
    // calculate duty, 8191 from 2 ^ 13 - 1
    value = value > 1000 ? 1000 : value;
    uint32_t duty = 3276 + (value * 3277) / 1000;
    // write duty to LEDC
    ledcWrite(LEDC_CHANNEL_B, duty);
}

// ch between 1-4
// value has to be between 0 and 1000
void setServo(uint8_t ch, uint32_t value) 
{
    // calculate duty, 8191 from 2 ^ 13 - 1
    value = value > 1000 ? 1000 : value;
    uint32_t duty = 205 + (value * 819) / 1000;
    // write duty to LEDC
    if (ch > 4 || ch < 1)
    {
        return;
    }
    ledcWrite(servo_ch[ch-1], duty);
}