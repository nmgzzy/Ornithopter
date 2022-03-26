#include "myIO.h"

Led::Led(uint8_t pin)
{
    pinMode(pin, OUTPUT);
}

void Led::ledOn()
{
    digitalWrite(pin, LOW);
    stat = LOW;
}

void Led::ledOff()
{
    digitalWrite(pin, HIGH);
    stat = HIGH;
}

void Led::ledTurn()
{
    stat = 1 - stat;
    digitalWrite(pin, stat);
}


Key::Key(uint8_t pin)
{
    pinMode(pin, INPUT);
}

int8_t Key::keyRead()
{
    stat = digitalRead(pin);
    return stat;
}

bool Key::isClick()
{
    last_stat = stat;
    stat = digitalRead(pin);
    if (last_stat == LOW && stat == HIGH)
        return true;
    return false;
}

