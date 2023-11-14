#ifndef INPUT_IOT_H
#define INPUT_IOT_H

#include "esp_err.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"

typedef void (*input_callback_t)(int);

typedef enum{
    LO_TO_HI = 1,
    HI_TO_LO = 2,
    ENYEDLE = 3
} interupt_typedef_edle_t;

void input_io_create(gpio_num_t gpio_num, interupt_typedef_edle_t type);
void input_io_get_level(gpio_num_t gpio_num);
void input_set_callback(void *cb);

#endif