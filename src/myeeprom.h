#ifndef __MYEEPROM_H__
#define __MYEEPROM_H__

#include "config.h"

void readEEPROM();
void writeEEPROM();
void json2par(const char* json);
void par2json(char* json, uint16_t len);

#endif