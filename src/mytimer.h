#ifndef __MYTIMER_H__
#define __MYTIMER_H__

#include "config.h"

extern bool timerEn;
extern hw_timer_t * timer;
extern uint time_count;
extern class PID pitchPID, rollPID, yawPID;

void timerSetup();

#endif