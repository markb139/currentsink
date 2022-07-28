#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "_dbg_.h"

const uint GPIO_A=2;
const uint GPIO_B=3;
uint slice_num;


void initialise_pwm(uint max_pwm)
{
    gpio_set_function(GPIO_A, GPIO_FUNC_PWM);
    gpio_set_function(GPIO_A, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO "GPIO_A" (it's slice GPIO_A)
    slice_num = pwm_gpio_to_slice_num(GPIO_A);
    _DBG_PRINT2("PWM Slice %d\n", slice_num);

    // Set period of 4 cycles (0 to 16383 inclusive. 14 bits)
    // clk freq = 125e6/16384 = 7629
    pwm_set_wrap(slice_num, max_pwm);
    
    // Set channel A output high for one cycle before dropping
    // pwm_set_chan_level(slice_num, PWM_CHAN_A, max_pwm >> 1);
    // pwm_set_chan_level(slice_num, PWM_CHAN_B, max_pwm >> 1);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
    
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
}

void set_level(uint level)
{
    pwm_set_chan_level(slice_num, PWM_CHAN_A, level);
}