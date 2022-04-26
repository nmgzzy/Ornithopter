#include "receiver.h"
#include "SBUS.h"

// #define SBUSRX 2
// #define SBUSTX 32

// a SBUS object, which is on hardware
// serial port 2
SBUS x8r(Serial2);

// channel, fail safe, and lost frames data
uint16_t channels[16];
bool failSafe;
bool lostFrame;

void receiverSetup()
{
	x8r.begin();
}

void receiverRead()
{
	x8r.read(channels, &failSafe, &lostFrame);
}

// uint32_t normaliseData(int value){
//   int minvalue = 172;
//   int maxvalue = 1811;
//   //normalise value to between 0 and 1000 for the set servo algorithm
//   uint32_t normalised_value = ((value - minvalue)/(maxvalue - minvalue))*1000;
//   return normalised_value;
// }