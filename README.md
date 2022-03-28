# ELEC6212 Biologically Inspired Robotics

IDE: VScode PlatformIO
MCU: ESP32 pico D4
Framework: Arduino



## Note⚠️:

- Update code before you start work.
- Each member should work on you branch and use merge request.
- Write a comment with date, name and what you write when you commit.
- Make sure there is no compile error before you push.
- Add comment in *todo list* below when you are working on a module so that others can know.
- feel free to add features in *todo list*



## TODO List:

### control

- [x] PID class
- [ ] balance control algorithm

### driver

- [x] Control motor
- [x] Control servo

### imu

- [x] Use library to read data
- [ ] Calculate angle (Joey is debuging)

### main

Feel free to write code in *main* for test, but don't commit *main* if necessary.

### myIO

- [x] led
- [x] Button (can add function if needed)

### mytimer

- [x] setup timer
- [ ] Timer interrupt function used to periodically read sensor control and control the motor

### mywifi (Joey is working)

- [ ] setup udp
- [ ] Send debug data to PC
- [ ] Receive instructions from PC

### receiver

- [ ] use SBUS library to read receiver data
- [ ] Decode data

### config.h

All head file should be included by config.h