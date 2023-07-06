// memory.h

#ifndef _MEMORY_h
#define _MEMORY_h

#include "arduino.h"

#define MEMORY_SIZE  0x10000

extern uint8_t  mem[];
extern uint16_t address;
extern uint8_t  data;

//externally supplied functions
void initmemory();

void readmemory();

void writememory();

#endif

