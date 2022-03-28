#include "myIO.h"

Led::Led(uint8_t _pin)
{
    pin = _pin;
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


// Key::Key(uint8_t _pin)
// {
//     pin = _pin;
//     pinMode(pin, INPUT);
// }

// int8_t Key::keyRead()
// {
//     stat = digitalRead(pin);
//     return stat;
// }

// uint8_t Key::isClick()
// {
//     last_stat = stat;
//     stat = digitalRead(pin);
//     if (stat == LOW) {
//         cnt++;
//     }
//     else {
//         cnt = 0;
//     }
//     if (last_stat == LOW && stat == HIGH) {
//         if (cnt > 100) {
//             return 2;
//         }
//         return 1;
//     }
//     return 0;
// }

void onBtn1Click(Button2& btn) 
{
    ESP.restart();
}

