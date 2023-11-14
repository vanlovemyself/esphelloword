/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "output_iot.h"
#include "input_iot.h"

TimerHandle_t xTimers[ 2 ];
EventGroupHandle_t xCreatedEventGroup;
#define BIT_BUTTON_PRESS	( 1 << 0 )
#define BIT_UART_HANDLE	    ( 1 << 1 )

void vtask1(void *pvParameters )
{
    for(;;)
    {
        EventBits_t uxBits = xEventGroupWaitBits(
            xCreatedEventGroup,   /* The event group being tested. */
            BIT_BUTTON_PRESS | BIT_UART_HANDLE, /* The bits within the event group to wait for. */
            pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
            pdFALSE,       /* Don't wait for both bits, either bit will do. */
            portMAX_DELAY );/* Wait a maximum of 100ms for either bit to be set. */

        if(uxBits && BIT_BUTTON_PRESS)
        {
            printf("PRESS BUTTON\n");
            output_io_toggle(2);
        }
        if(uxBits && BIT_UART_HANDLE )
        {

        }

    }
}

void vTimerCallback( TimerHandle_t xTimer )
 {
 uint32_t ulCount;

    /* Optionally do something if the pxTimer parameter is NULL. */
    configASSERT( xTimer );

    /* The number of times this timer has expired is saved as the
    timer's ID.  Obtain the count. */
    ulCount = ( uint32_t ) pvTimerGetTimerID( xTimer );


    /* If the timer has expired 10 times then stop it from running. */
    if( ulCount == 0 )
    {
        output_io_toggle(2);
    }
    else if(ulCount == 1)
    {
       printf("iu my\n");
    }
 }


void button_callback(int pin)
{
    if(pin == GPIO_NUM_0)
    {
        BaseType_t pxHigherPriorityTaskWoken;
        xEventGroupSetBitsFromISR(xCreatedEventGroup,BIT_BUTTON_PRESS,&pxHigherPriorityTaskWoken);
    }
}

void app_main(void)
{
    xTimers[0] = xTimerCreate("timer1", pdMS_TO_TICKS(500), pdTRUE, (void*) 0, vTimerCallback);
    xTimers[1] = xTimerCreate("timer2", pdMS_TO_TICKS(1000), pdTRUE, (void*) 1, vTimerCallback);
    
    output_io_create(2);
    input_io_create(0, HI_TO_LO);
    input_set_callback(button_callback);

    xCreatedEventGroup = xEventGroupCreate();

    // xTimerStart(xTimers[0],0);
    // xTimerStart(xTimers[1],0);

    xTaskCreate(vtask1, "vtask1", 1024, NULL, 4, NULL);

}
