#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "config.h"

void PWMSetup();
void setBrushless(uint32_t value);
void setServo(uint8_t ch, uint32_t value);

#endif