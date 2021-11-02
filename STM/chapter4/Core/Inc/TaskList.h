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


void TL_init();
void TL_insertFront(STask* d);
void TL_insertOrder(STask* t);
uint8_t TL_deleteID(uint32_t id);
STask* TL_deleteFront();
STask* TL_getCurrent(void);

uint8_t TL_pointNext(void);
void TL_pointStart(void);
void TL_pointMark(void);
void TL_restoreMark(void);
uint32_t TL_size(void);


#endif /* INC_TASKLIST_H_ */
