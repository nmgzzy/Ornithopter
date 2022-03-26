#include "control.h"


int PID::compute(float measurement, float target)
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