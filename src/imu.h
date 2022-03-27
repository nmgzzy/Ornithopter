#ifndef __IMU_H__
#define __IMU_H__

#include "config.h"
#include "MPU9250.h"

extern MPU9250 mpu;

void IMUsetup();
void print_roll_pitch_yaw();
void print_acc_gyro();
void print_quaternion();

#endif