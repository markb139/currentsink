#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "bsp/board.h"
#include "tusb.h"
#include "usbtmc_app.h"

#include "_dbg_.h"    

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9


extern void initialise_pwm(uint max_pwm);
extern void set_level();
extern void initialise_adc(const uint adc);

const uint16_t LED_PIN = 16;
const uint16_t LED_PIN2 = 17;

void led_blinking_task(void);
void led_indicator_pulse();
void initialise_pwm(uint max_pwm);

/*------------- MAIN -------------*/
int main(void)
{
  board_init();
  gpio_init(LED_PIN);
  gpio_init(LED_PIN2);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_set_dir(LED_PIN2, GPIO_OUT);
    
  _DBG_PRINT("starting\n");

  initialise_pwm(2048);
  initialise_adc(0);
  initialise_adc(1);

  led_indicator_pulse();

  tusb_init();

  while (1)
  {
    tud_task(); // tinyusb device task
    usbtmc_app_task_iter();
    led_blinking_task();
  }

  return 0;
}
/* Blink pattern
 * - 250 ms  : device not mounted
 * - 0 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250000,
  BLINK_MOUNTED = 2500000,
  BLINK_SUSPENDED = 2500000,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;


//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  _DBG_PRINT("tud_mount_cb\n");
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  _DBG_PRINT("tud_umount_cb\n");
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// BLINKING TASK + Indicator pulse
//--------------------------------------------------------------------+


volatile uint8_t doPulse = true;
// called from USB context
void led_indicator_pulse(void) {
	doPulse = true;
}

void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;
  if(blink_interval_ms == BLINK_MOUNTED) // Mounted
  {
    if(doPulse)
    {
      led_state = true;
      gpio_put(LED_PIN, 1);

      start_ms = time_us_32();
      doPulse = false;
    }
    else if (led_state == true)
    {
      if ( time_us_32() - start_ms < 750000) //Spec says blink must be between 500 and 1000 ms.
      {
        return; // not enough time
      }
      led_state = false;
      gpio_put(LED_PIN, 0);
    }
  }
  else
  {
    // Blink every interval ms
    if (  time_us_32() - start_ms < blink_interval_ms) return; // not enough time
    start_ms += blink_interval_ms;

    gpio_put(LED_PIN, led_state);

    led_state = 1 - led_state; // toggle
  }
}
