#include "control.h"
#include "receiver.h"

PID pitchPID, rollPID, yawPID;

void PID::compute(float measurement, float target)
{
    error = target - measurement;
    integration += error;
    integration = integration >  integLimit ?  integLimit : integration;
    integration = integration < -integLimit ? -integLimit : integration;
    output = Kp * error + Kd * (error - last_error) + Ki * integration;
    output = output > outputUpLimit ? outputUpLimit : output;
    output = output < outputDownLimit ? outputDownLimit : output;
    last_error = error;
}

void control()
{
    static int output0, output1, output2, output3, output4;
    receiverRead();
    if (mpu.update())
    {
        pitchPID.compute(mpu.getPitch(), channels[1]-992);
        rollPID.compute(mpu.getRoll(), channels[0]-992);
        yawPID.compute(mpu.getGyroZ(), channels[3]-992);
        output1 = 500 + pitchPID.output + rollPID.output + yawPID.output;
        output2 = 500 - pitchPID.output + rollPID.output + yawPID.output;
        output3 = 500 - pitchPID.output - rollPID.output + yawPID.output;
        output4 = 500 + pitchPID.output - rollPID.output + yawPID.output;
        output0 = map(channels[2], 190, 1790, 0, 800);
        if (SystemMode == 2) {
            setBrushless(output0);
            setServo(1, output1);
            setServo(2, output2);
            setServo(3, output3);
            setServo(4, output4);
        }
        else if (SystemMode == 0){
            setBrushless(0);
            setServo(1, output1);
            setServo(2, output2);
            setServo(3, output3);
            setServo(4, output4);
        }
        else {
            setBrushless(0);
            setServo(1, 500);
            setServo(2, 500);
            setServo(3, 500);
            setServo(4, 500);
        }
    }
    else
    {
        Serial.println("mpu read error");
    }
}