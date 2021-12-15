#ifndef __COMMANDS__H__
#define __COMMANDS__H__

#include "stddef.h"

static double _set_current=0.0;;

char _buffer[32];

static const char idn[] = "Rasp Pico CurrentSink,0.1,1000,v1.0\r\n";
static const char opc_1[] = "1\r\n";
static const char opc_0[] = "0\r\n";
static const char OK[] = "OK\r\n";

void process_idn(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen);
void process_set(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen);
void process_get_set(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen);
void process_read(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen);
void process_voltage_read(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen);
void process_led_set(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen);

typedef struct {
    const char* name;
    void (*func)(uint8_t const*, size_t, size_t);
} command_t;

#define _CMD(_CMD_STR, _FUNC) {_CMD_STR, _FUNC}

command_t table[] = {
    _CMD("*idn?", process_idn),
    _CMD("current:set?", process_get_set),
    _CMD("current:set", process_set),
    _CMD("current:read?", process_read),
    _CMD("voltage:read?", process_voltage_read),
    _CMD("led:set", process_led_set)
};

#define CMDS sizeof(table)/sizeof(command_t)


#endif