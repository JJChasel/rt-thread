/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-25     LongfeiMa    the first version for stm32h7xx
 */
#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "rtdevice.h"
#include "board.h"

#ifdef RT_USING_PIN

/* defines */
enum _LedEnum
{
    BOARD_LD_3 = 75,
    BOARD_LD_2 = 137
};

typedef enum _LedEnum LedDesc;

#define BOARD_LED_BLUE BOARD_LD_2
#define BOARD_LED_RED  BOARD_LD_3

enum _LedStatusEnum
{
    BOARD_LED_ON = 0,
    BOARD_LED_OFF
};

typedef enum _LedStatusEnum LedStatus;

/* APIs for application */
void led_write(LedDesc led, LedStatus onoff);

#define led_off() (led_write(BOARD_LED_RED, BOARD_LED_OFF))
#define led_on()  (led_write(BOARD_LED_RED, BOARD_LED_ON))

#else

#define led_on()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)
#define led_off()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)

int led_hw_init(void);

#endif // ifdef(RT_USING_PIN)
#endif
