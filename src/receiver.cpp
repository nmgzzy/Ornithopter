#include "receiver.h"
#include "SBUS.h"

// #define SBUSRX 2

SBUS x8r(Serial2);

// channel, fail safe, and lost frames data
uint16_t channels[16];
bool failSafe;
bool lostFrame;
uint8_t SystemMode = 0; //0-debug; 1-safe mode; 2-run;
uint8_t SafeFlag = 0;
int16_t resetCnt = 0;

bool isIn(int16_t x, int16_t y) {
    return (x <= y+100 && x >= y-100);
}

void receiverSetup()
{
	x8r.begin();
}

void receiverRead()
{
	x8r.read(channels, &failSafe, &lostFrame);
	// for (uint8_t i = 0; i < 4; i++) {
	// 	channels[i] = channels[i] < 190 ? 190 : channels[i];
	// 	channels[i] = channels[i] > 1790 ? 1790 : channels[i];
	// }
	if (SafeFlag == 0 && isIn(channels[5], 190)) {  //unlock
        SafeFlag = 1;
    }
    if (SafeFlag == 1) {
        if (isIn(channels[5], 190)) {
            SystemMode = 0;
        }
        else if (isIn(channels[5], 992)){
            SystemMode = 1;
        }
        else if (isIn(channels[5], 1790)){
            SystemMode = 2;
        }
    }
    if(isIn(channels[6], 1790)) {  //reset
        resetCnt++;
        if (resetCnt > 200) {
            ESP.restart();
        } 
    }
    else {
        resetCnt = 0;
    }
}



// uint32_t normaliseData(int value){
//   int minvalue = 172;
//   int maxvalue = 1811;
//   //normalise value to between 0 and 1000 for the set servo algorithm
//   uint32_t normalised_value = ((value - minvalue)/(maxvalue - minvalue))*1000;
//   return normalised_value;
// }

/*
左摇杆
上下/油门	ch2		190-1790  992
左右yaw		ch3		190-1790
右摇杆
上下pitch		ch1	
左右roll		ch0  

*/