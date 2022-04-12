#ifndef __MYTIMER_H__
#define __MYTIMER_H__

#include "config.h"

extern bool timerEn;
extern hw_timer_t * timer;
extern uint time_count;

void timerSetup();

#endif