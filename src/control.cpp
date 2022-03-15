#include "control.h"

class PID
{
public:
    float Kp = 0, Ki = 0, Kd = 0;
    float error = 0, last_error = 0;
    float integration = 0;
    float integLimit = 0;
    float outputUpLimit = 1000;
    float outputDownLimit = 0;

    int compute(float measurement, float target)
    {
        error = target - measurement;
        integration += error;
        integration = integration >  integLimit ?  integLimit : integration;
        integration = integration < -integLimit ? -integLimit : integration;
        float output = Kp * error + Kd * (error - last_error) + Ki * integration;
        output = output > outputUpLimit ? outputUpLimit : output;
        output = output < outputDownLimit ? outputDownLimit : output;
        last_error = error;
        return (int)output;
    }
};