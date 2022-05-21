#include "control.h"
#include "receiver.h"

PID pitchPID, rollPID, yawPID;
int power = 0;

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
        // pitchPID.compute(mpu.getPitch(), channels[1]-992);
        // rollPID.compute(mpu.getRoll(), channels[0]-992);
        // yawPID.compute(mpu.getGyroZ(), channels[3]-992);
        if(flag_r == 1)
        {
            pitchPID.compute(0, channels[1]-992.0);
            rollPID.compute(0, channels[0]-993.0);
            yawPID.compute(0, channels[3]-990.0);
            output0 = map(channels[2], 190, 1790, 0, 800);
        }
        else if(flag_r == 2){
            pitchPID.compute(0, chjoy[3]);
            rollPID.compute(0, chjoy[2]);
            yawPID.compute(0, chjoy[0]);
            power += chjoy[1] / 10;
            power = power > 800 ? 800 : power;
            power = power < 0 ? 0 : power;
            output0 = power;
        }
        output1 = 500 + pitchPID.output - rollPID.output + yawPID.output;
        output2 = 500 - pitchPID.output - rollPID.output + yawPID.output;
        output3 = 500 - pitchPID.output + rollPID.output + yawPID.output;
        output4 = 500 + pitchPID.output + rollPID.output + yawPID.output;
        debug_datai[2] = output0;
        debug_datai[0] = output1;
        debug_datai[1] = output2;
        debug_datai[2] = output3;
        debug_datai[3] = output4;

        if (SystemMode == 2) {
            setBrushless(output0);
            setServo(1, output1);
            setServo(2, output2);
            setServo(3, output3);
            setServo(4, output4);
        }
        else if (SystemMode == 1){
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