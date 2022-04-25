#include "receiver.h"

// a SBUS object, which is on hardware
// serial port 2
SBUS x8r(Serial2);

// channel, fail safe, and lost frames data
uint16_t channels[16];
bool failSafe;
bool lostFrame;

void receiverSetup() {
  // begin the SBUS communication
  x8r.begin();
}

void receiverLoop() {

  // look for a good SBUS packet from the receiver
  if(x8r.read(&channels[0], &failSafe, &lostFrame)){
    for (uint8_t i = 0; i < 16; i++)
    {
      Serial.printf("%d  ", channels[i]);
    }
    Serial.println("");
    
    // write the SBUS packet to an SBUS compatible servo
    //x8r.write(&channels[0]);
  }
}

// uint32_t normalise_data(int value){
//   int minvalue = 172;
//   int maxvalue = 1811;
//   //normalise value to between 0 and 1000 for the set servo algorithm 
//   uint32_t normalised_value = ((value - minvalue)/(maxvalue - minvalue))*1000;
//   return normalised_value;
// }

// void loop() {
//   //one method uses .read, when a complete packet is received this returns true, the channels[0-15], failsafe and lost frame data
  
//   // if(x8r.read(&channels[0], &failSafe, &lostFrame)){
//   //   Serial.println(channels[0]); //prints the contents of channel0 every time a packet is receive
//   // }

//   //readCal allows for the same functionality with additional calibration 
//   //The data from channels [0-15] is calibrated to a +/1.0 float value assuming a linear relationship
//   //based on the minimum and maximum value or endpoints for each channel. By default hese are set to 172 and 1811.
//   //This mapping to a +/- 1.0 float value assumes a linear relationship based on the minimum and maximum endpoints for each channel

//   if(x8r.readCal(channels, &failSafe, &lostFrame)){
//     //Complete packet is received, prints the calibrated value of channel 0 every time a valid SBUS packet is received
//     Serial.println(channels[0]);
//     uint32_t value = channels[0];
//     //get normalised value because SetServo only accepts values between 0 and 1000
//     uint32_t new_value = normalise_data(value);
//     //manually setting the value of each servo, currently all four servos are set the same 
//     setServo(1, new_value);
//     setServo(2, new_value);
//     setServo(3, new_value);
//     setServo(4, new_value);

//   }
//   //writing the packet to a servo, this uses the inbuilt SBUS functionality and would require the channel[16] definition at the top of code to change from float to uint16_t
//   //x8r.write(&channels[0]);
  
// }