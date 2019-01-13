#ifndef __DRV_BUTTON_H__
#define __DRV_BUTTON_H__

#include "board.h"

#define BOARD_USERBUTTON (7)

#define BUTTON_STATE_RELEASED 0
#define BUTTON_STATE_PRESSING 1

int button_hw_init(void);
void button_set_callback(void (*cb)(void *args), void *args);
int button_read(void);

#endif
