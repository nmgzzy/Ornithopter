#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "config.h"

class PID
{
public:
    float Kp = 1, Ki = 0, Kd = 0;
    float output = 0;
    float integLimit = 10;
    float outputUpLimit = 500;
    float outputDownLimit = -500;

    void compute(float measurement, float target);

private:
    float error = 0, last_error = 0;
    float integration = 0;
};

extern PID pitchPID, rollPID, yawPID;

void control();

#endif