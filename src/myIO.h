#ifndef __MYIO_H__
#define __MYIO_H__

#include "config.h"

#define LED_PIN  4
#define KEY1_PIN 34
#define KEY2_PIN 35

class Led
{
public:
    uint8_t pin;
    uint8_t stat = HIGH;

    Led(uint8_t pin);
    void ledOn();
    void ledOff();
    void ledTurn();
};

class Key
{
public:
    uint8_t pin;
    uint8_t stat = HIGH;
    uint8_t last_stat = HIGH;

    Key(uint8_t pin);
    int8_t keyRead();
    bool isClick();
};

#endif