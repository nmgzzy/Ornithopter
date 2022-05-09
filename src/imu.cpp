#include "imu.h"

MPU9250 mpu;

void IMUsetup() {
    Wire.begin();
    delay(200);

    MPU9250Setting setting;
    setting.accel_fs_sel = ACCEL_FS_SEL::A8G;
    setting.gyro_fs_sel = GYRO_FS_SEL::G1000DPS;
    setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
    setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
    setting.gyro_fchoice = 0x03;
    setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
    setting.accel_fchoice = 0x01;
    setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;

    while (!mpu.setup(0x68, setting)) {  // change to your own address
        Serial.println("MPU connection failed.");
        delay(2000);
    }
    Serial.println("MPU connection success.");
}

void print_roll_pitch_yaw() 
{
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.println(mpu.getRoll(), 2);
}

void print_acc_gyro() 
{
    Serial.print("acc_gyro: ");
    Serial.printf("%04.2f %04.2f %04.2f  ", mpu.getAcc(0), mpu.getAcc(1), mpu.getAcc(2));
    Serial.printf("%05.2f %05.2f %05.2f\n", mpu.getGyro(0), mpu.getGyro(1), mpu.getGyro(2));
}

void print_quaternion() 
{
    Serial.print("quaternion: ");
    Serial.printf("%.2f  %.2f  %.2f  %.2f\n", mpu.getQuaternionX(), mpu.getQuaternionY(), mpu.getQuaternionZ(), mpu.getQuaternionW());
}
