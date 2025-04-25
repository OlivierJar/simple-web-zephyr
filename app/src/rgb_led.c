#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>

#include "rgb_led.h"

#define PERIOD (USEC_PER_SEC / 100)

static const struct pwm_dt_spec red_pwm_led =
	PWM_DT_SPEC_GET(DT_ALIAS(red_pwm_led));
static const struct pwm_dt_spec green_pwm_led =
	PWM_DT_SPEC_GET(DT_ALIAS(green_pwm_led));
static const struct pwm_dt_spec blue_pwm_led =
	PWM_DT_SPEC_GET(DT_ALIAS(blue_pwm_led));

static const struct gpio_dt_spec led=
	GPIO_DT_SPEC_GET(DT_ALIAS(led0_green),gpios);

int rgb_led_init()
{
	if (!device_is_ready(red_pwm_led.dev) ||
	    !device_is_ready(green_pwm_led.dev) ||
	    !device_is_ready(blue_pwm_led.dev)
    ) {
		return -ENODEV;
	}
    return 0;
}

void rgb_led_set(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t pulse_red, pulse_green, pulse_blue;

    pulse_red = (red_pwm_led.period >> 8) * r;
    pulse_green = (green_pwm_led.period >> 8) * g;
    pulse_blue = (blue_pwm_led.period >> 8) * b;

    if( pwm_set_pulse_dt(&red_pwm_led, pulse_red) != 0 ||
        pwm_set_pulse_dt(&green_pwm_led, pulse_green) != 0 ||
        pwm_set_pulse_dt(&blue_pwm_led, pulse_blue) != 0) {
        printk("Error setting RGB PWM\n");
    }
}
int init_led(){
    if (!gpio_is_ready_dt(&led)) {
		return -ENODEV;
	}
    if (0!=gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE)){
        return -ENODEV;
    }

}
void toggle_led(){
    int ret;
    ret = gpio_pin_toggle_dt(&led);
    
}