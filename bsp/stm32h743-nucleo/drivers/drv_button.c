#include "board.h"
#include "drv_button.h"
#include <rtthread.h>
#include <rtdevice.h>

#ifndef RT_USING_PIN
#error "Button support required GPIO driver!"
#endif

void button_set_callback(void (*cb)(void *args), void *args)
{
    if(RT_NULL == cb)
    {
        rt_pin_detach_irq(BOARD_USERBUTTON);
        rt_pin_irq_enable(BOARD_USERBUTTON, PIN_IRQ_DISABLE);
    }
    else
    {
        rt_pin_attach_irq(BOARD_USERBUTTON, PIN_IRQ_MODE_RISING, cb, args);
        rt_pin_irq_enable(BOARD_USERBUTTON, PIN_IRQ_ENABLE);
    }
}

int button_read(void)
{
    return rt_pin_read(BOARD_USERBUTTON);
}

int button_hw_init(void)
{
    rt_pin_mode(BOARD_USERBUTTON, PIN_MODE_INPUT);
    button_set_callback(RT_NULL, NULL);
    return 0;
}

INIT_APP_EXPORT(button_hw_init);
