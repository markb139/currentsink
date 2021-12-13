#ifndef __COMMANDS__H__
#define __COMMANDS__H__

#include "stddef.h"

static double _set_current=0.0;;

char _buffer[32];

static const char idn[] = "Rasp Pico CurrentSink,0.1,1000,v1.0\r\n";
static const char opc_1[] = "1\r\n";
static const char opc_0[] = "0\r\n";
static const char OK[] = "OK\r\n";

extern bool command_complete(uint8_t const *aBuffer, size_t aLen);

#endif