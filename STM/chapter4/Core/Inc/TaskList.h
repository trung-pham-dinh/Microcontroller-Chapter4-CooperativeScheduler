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

#define SCH_MAX_TASK	40;

typedef struct {
	void(*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} STask;

void TL_insertFront(STask* d);
void TL_deleteID(uint32_t id);
STask* TL_getCurrent();

uint8_t TL_pointNext();
void TL_pointStart();
void TL_pointMark();
void TL_restoreMark();


#endif /* INC_TASKLIST_H_ */
