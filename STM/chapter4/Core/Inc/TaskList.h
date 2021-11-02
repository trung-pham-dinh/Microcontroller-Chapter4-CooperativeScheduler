/*
 * TaskList.h
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */

#ifndef INC_TASKLIST_H_
#define INC_TASKLIST_H_

#include "main.h"
#include <stdlib.h>

typedef struct {
	void(*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} STask;

void TL_init(void);
void TL_insert(STask*t);
STask* TL_removeFront(void);
STask* TL_getFront();


#endif /* INC_TASKLIST_H_ */
