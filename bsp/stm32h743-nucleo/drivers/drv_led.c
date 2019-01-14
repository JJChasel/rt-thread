/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-25     LongfeiMa    the first version for stm32h7xx
 */
#include <rtconfig.h>
#include <rtdevice.h>
#include <board.h>

#include "drv_led.h"

#include <string.h>
#include <stdbool.h>

static rt_thread_t g_tled = RT_NULL;

void led_write(LedDesc led, LedStatus onoff)
{
	rt_pin_write((rt_base_t)led, (BOARD_LED_ON == onoff) ? PIN_HIGH : PIN_LOW);
}

static void led_thread_entry(void *parameter)
{
	while (1)
	{
		led_on();
		rt_thread_delay(RT_TICK_PER_SECOND);
		led_off();
		rt_thread_delay(RT_TICK_PER_SECOND);
	}
}

static void led_cleanup(rt_thread_t tid)
{
	(void)tid;
	led_off();
	g_tled = 0;
}

#ifndef RT_USING_PIN
int led_hw_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* Configure GPIO pin: PI1 (LD2) */
	GPIO_InitStruct.Pin   = GPIO_PIN_14;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	return 0;
}
INIT_BOARD_EXPORT(led_hw_init);
#else
int led_hw_init(void)
{	
	rt_pin_mode((rt_base_t)BOARD_LED_BLUE, PIN_MODE_OUTPUT);
	rt_pin_mode((rt_base_t)BOARD_LED_RED, PIN_MODE_OUTPUT);

	return 0;
}
INIT_APP_EXPORT(led_hw_init);
#endif

int led_run(void)
{
	rt_thread_t tid;

	if(RT_NULL != g_tled)
	{
		rt_kprintf("led already running...\n");
		return 1;
	}

	tid = rt_thread_create("led",
						   led_thread_entry, RT_NULL,
						   512, 12, 5);

	if (tid != RT_NULL)
	{
		tid->cleanup = led_cleanup;
		g_tled = tid;
		rt_thread_startup(tid);
	}

	return 0;
}
MSH_CMD_EXPORT(led_run, run led);

int led_stop(void)
{
	if(RT_NULL == g_tled)
	{
		rt_kprintf("led is not running...\n");
		return 1;
	}
	rt_thread_delete(g_tled);
	return 0;
}
MSH_CMD_EXPORT(led_stop, stop led);

int led_ctrl(int arg, char *args[])
{
	/* check params */
	char *help = "param error. eg. \"led_ctrl led2 on\"\n";
	if (arg != 3)
	{
		rt_kprintf("%s", help);
		return 1;
	}
	bool param1_ok = 0 == strcmp(args[1], "led2") || 0 == strcmp(args[1], "led3");
	bool param2_ok = 0 == strcmp(args[2], "on") || 0 == strcmp(args[2], "off");
	if (param1_ok && param2_ok)
	{
		if (0 == strcmp(args[1], "led2"))
			led_write(BOARD_LD_2, (0 == strcmp(args[2], "on")) ? BOARD_LED_ON : BOARD_LED_OFF);
		else
			led_write(BOARD_LD_3, (0 == strcmp(args[2], "on")) ? BOARD_LED_ON : BOARD_LED_OFF);

		return 0;
	}
	else
	{
		rt_kprintf("%s", help);
		return 1;
	}
}
MSH_CMD_EXPORT(led_ctrl, control specific led);
