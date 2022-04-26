#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "config.h"

class PID
{
public:
    float Kp = 0, Ki = 0, Kd = 0;
    float output = 0;
    float integLimit = 10;
    float outputUpLimit = 1000;
    float outputDownLimit = -1000;

    void compute(float measurement, float target);

private:
    float error = 0, last_error = 0;
    float integration = 0;
};

extern PID pitchPID, rollPID, yawPID;

void control();

#endif