#ifndef OUTPUT_IOT_H
#define OUTPUT_IOT_H

#include "esp_err.h"
#include "hal/gpio_types.h"

void output_io_create(gpio_num_t gpio_num);

void output_io_toggle(gpio_num_t gpio_num);

#endif