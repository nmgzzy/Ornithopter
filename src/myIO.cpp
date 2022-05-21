#include "myIO.h"

// Button2 btn1, btn2;

Led::Led(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
    on();
}

void Led::on()
{
    digitalWrite(pin, LOW);
    stat = LOW;
}

void Led::off()
{
    digitalWrite(pin, HIGH);
    stat = HIGH;
}

void Led::turn()
{
    stat = 1 - stat;
    digitalWrite(pin, stat);
}

void Led::blink()
{
    unsigned long a =  millis();
    if(a - lasttime > period * (3 - SystemMode))
    {
        lasttime = a;
        turn();
    }
}

// void onBtn1Click(Button2& btn) 
// {
//     // writeEEPROM();
// }

// void onBtn2Click(Button2& btn) 
// {
//     // writeEEPROM();
// }

// void onBtn1DoubleClick(Button2& btn) 
// {
//     ESP.restart();
// }

// void onBtn2DoubleClick(Button2& btn) 
// {
//     if (SystemMode == 0) {
//         SystemMode = 1;
//     }
//     else if (SystemMode == 1 && channels[2] < 200) {
//         SystemMode = 2;
//     }
// }

// void onBtn12Pressed(Button2& btn) 
// {
//     static uint8_t t = 0;
//     if (btn2.getState() == LOW){
//         t++;
//         if (t > 100) {
//             ESP.restart();
//         }
//     }
//     else {
//         t = 0;
//     }
// }

// void BtnSetup()
// {
//     btn1.begin(KEY1_PIN);
//     btn2.begin(KEY2_PIN);
//     btn1.setClickHandler(onBtn1Click);
//     btn2.setClickHandler(onBtn2Click);
//     btn1.setDoubleClickHandler(onBtn1DoubleClick);
//     btn2.setDoubleClickHandler(onBtn2DoubleClick);
//     // btn1.setPressedHandler(onBtn12Pressed);

// }


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
//         else if( cnt > 5){
//             return 1;
//         }
//     }
//     return 0;
// }
