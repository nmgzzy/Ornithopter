#ifndef __BLE_H__
#define __BLE_H__

#include "config.h"

extern int8_t chjoy[4];
extern uint8_t flag_r;
extern int debug_datai[4];
extern float debug_dataf[4];

void BLEsetup();
void BLEloop();

#endif