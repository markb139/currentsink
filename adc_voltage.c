#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "_dbg_.h"    

void initialise_adc(const uint ADC)
{
    const float conversion_factor = 3.3f / (1 << 12);
    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26+ADC);
    // Select ADC input 0 (GPIO26)
    adc_select_input(ADC);
}

uint16_t read_adc(const uint adc) 
{
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result=0;
    uint32_t runing_result=0;
    adc_select_input(adc);
    for(uint i=0;i<16;i++)
    {
        runing_result += adc_read();
        sleep_us(1000);
    }
    result = runing_result >> 4;
     
    _DBG_PRINT3("Raw value: 0x%04x, voltage: %f V\n", result, result * conversion_factor);
    return result;
}
