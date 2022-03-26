#ifndef __IMU_H__
#define __IMU_H__

#include "config.h"
#include "MPU9250.h"

extern MPU9250 mpu;

void IMUsetup();
void printQuaternion();
void print_roll_pitch_yaw();

#endif