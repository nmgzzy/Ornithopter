#include "mytimer.h"

hw_timer_t *timer = NULL;
// volatile SemaphoreHandle_t timerSemaphore;
// portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
bool timerEn = true;

int WAIT_TIME = 1000000;

void IRAM_ATTR onTimer()
{
  // // Increment the counter and set the time of ISR
  // portENTER_CRITICAL_ISR(&timerMux);

  // work here

  // portEXIT_CRITICAL_ISR(&timerMux);
  // // Give a semaphore that we can check in the loop
  // xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // // It is safe to use digitalRead/Write here if you want to toggle an output

  // output the data received from the sensor pin (GYRO SENSOR)?
  Serial.println("Printing periodic sensor data...");
  Serial.print("Acceleration: [ X:");
  Serial.print(mpu.getAccX());
  Serial.print(", Y:");
  Serial.print(mpu.getAccY());
  Serial.print(", Z:");
  Serial.print(mpu.getAccZ());
  Serial.println("]");

  Serial.print("Acceleration: [ X:");
  Serial.print(mpu.getGyroX());
  Serial.print(", Y:");
  Serial.print(mpu.getGyroY());
  Serial.print(", Z:");
  Serial.print(mpu.getGyroZ());
  Serial.println("]");
}

void timerSetup()
{
  // Create semaphore to inform us when the timer has fired
  // timerSemaphore = xSemaphoreCreateBinary();

  // Use 1st timer of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(0, 80, true);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, WAIT_TIME, true);

  // Start an alarm
  timerAlarmEnable(timer);
}

/*
void loop() {
  // If Timer has fired
  // if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
  //   // Read the interrupt count and time
  //   portENTER_CRITICAL(&timerMux);

  //   portEXIT_CRITICAL(&timerMux);
  // }
  // If timerEn is false
  if (timerEn == false && timer != NULL) {
    // If timer is still running
    if (timer) {
      // Stop and free timer
      timerEnd(timer);
      timer = NULL;
    }
  }
}
*/