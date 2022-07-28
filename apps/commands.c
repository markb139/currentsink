#include "string.h"
#include <stdio.h>
#include <stdlib.h>  
#include "pico/stdlib.h"

#include "main.h"
#include "commands.h"
#include "_dbg_.h"    


extern void set_level(uint level);
extern uint16_t read_adc(const uint adc);
extern bool command_complete(uint8_t const *aBuffer, size_t aLen);

bool process_command(uint8_t* aData, size_t aLen)
{
    if(aLen == 0)
        return false;

    _DBG_PRINT2("CMD: %s\n", aData);
    for(uint16_t i=0;i<CMDS;i++) {
        command_t cur = table[i];
        // _DBG_PRINT2("name %s\n", cur.name);
        if(!strncasecmp(cur.name, aData, strlen(cur.name))) {
            aData[aLen] = 0;
            cur.func(aData, aLen, strlen(cur.name));
            break;
        }
    }
    return true;
}

void process_idn(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen)
{
    _DBG_PRINT2("%s\n", idn);
    command_complete(idn, strlen(idn));
}

void process_set(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen)
{
    uint level = 0;

    _set_current = atof((char*) aBuffer + aCmdLen + 1);
    level = (uint) ((2048*_set_current) / 3.3);
    set_level(level);
    _DBG_PRINT3("Set current %.8f integer level 0x%04x\n", _set_current, level);
}

void process_get_set(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen)
{
    sprintf(_buffer, "%f\r\n",_set_current);
    command_complete(_buffer, strlen(_buffer));
}

void process_read(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen)
{
    uint16_t level = 0;
    double current = 0.0;
    level = read_adc(0);
    current = (double)((level * 3.3) / 4096);
    sprintf(_buffer, "%f\r\n",current);
    command_complete(_buffer, strlen(_buffer));
}

void process_voltage_read(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen)
{
    uint16_t level = 0;
    double voltage = 0.0;
    level = read_adc(1);
    voltage = (double)((level * 3.3) / 4096);
    sprintf(_buffer, "%f\r\n", voltage);
    command_complete(_buffer, strlen(_buffer));
}

void process_led_set(uint8_t const *aBuffer, size_t aLen, size_t aCmdLen)
{
    uint16_t led_state = atoi((char*) aBuffer + aCmdLen + 1);
    _DBG_PRINT2("LED %d\n", led_state);
    gpio_put(16, led_state);
}