/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2017-08-25     LongfeiMa    transplantation for stm32h7xx
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32h7xx.h>
#include "stm32h7xx_hal.h"

// <o> SDCard Driver <1=>SDIO sdcard <0=>SPI MMC card
//  <i>Default: 1
#define STM32_USE_SDIO          0

/* whether use board external SDRAM memory */
// <e>Use external SDRAM memory on the board
//  <o>Begin Address of External SDRAM
#define EXT_SDRAM_BEGIN    0xC0000000
//  <o>Size of External SDRAM
#define EXT_SDRAM_SIZE     (0x800000)
#define EXT_SDRAM_END      (EXT_SDRAM_BEGIN + EXT_SDRAM_SIZE)
// </e>

#ifdef __CC_ARM
#define HEAP_BEGIN    (0x24000000)  // bind start addr to the AXI SRAM, this is the largest continues RAM in H7
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

// <o> Internal SRAM memory size[Kbytes] <8-64>
//  <i>Default: 64
#define STM32_SRAM_SIZE   (512 * 1024)
#define HEAP_END          (HEAP_BEGIN + STM32_SRAM_SIZE)

void rt_hw_board_init(void);

#endif

