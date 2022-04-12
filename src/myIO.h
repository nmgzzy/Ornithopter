#ifndef __MYIO_H__
#define __MYIO_H__

#include "config.h"
#include "Button2.h"

#define LED_PIN  4
#define KEY1_PIN 34
#define KEY2_PIN 35

class Led
{
public:
    uint8_t pin = LED_PIN;
    uint8_t stat = HIGH;

    Led(uint8_t pin);
    void ledOn();
    void ledOff();
    void ledTurn();
};

// class Key
// {
// public:
//     uint8_t pin;
//     uint8_t stat = HIGH;
//     uint8_t last_stat = HIGH;
//     uint16_t cnt = 0;

//     Key(uint8_t pin);
//     int8_t keyRead();
//     uint8_t isClick();
// };

void onBtn1Click(Button2& btn);
void onBtn2Click(Button2& btn);

#endif