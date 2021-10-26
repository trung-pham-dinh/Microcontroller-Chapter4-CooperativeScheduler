/*
 * Scheduler.c
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */
#include "Scheduler.h"

static uint32_t hashID = 0;

uint32_t INTERRUPT_PERIOD = 0;
const uint32_t SYS_CLK_FREQ = 8000;

void SCH_Init(TIM_HandleTypeDef *htim) {
	INTERRUPT_PERIOD = (htim->Instance->PSC+1)*(htim->Instance->ARR+1) / SYS_CLK_FREQ;
	if(INTERRUPT_PERIOD == 10) HAL_GPIO_WritePin(DEBUG3_GPIO_Port, DEBUG3_Pin, 1);
}

uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD) {
	STask* task = (STask*)malloc(sizeof(STask));
	task->pTask = pFunc;
	task->Delay = DELAY;
	task->Period = PERIOD;
	task->RunMe = 0;
	task->TaskID = hashID;

	TL_insertFront(task);

	hashID++;
	return hashID-1;
}

void SCH_Dispatch_Tasks(void) {
	TL_pointStart();
	STask* task = NULL;
	do {
		task = TL_getCurrent();
		if(task->RunMe > 0) {
			(*(task->pTask))();
			(task->RunMe)--;
			if(task->Period == 0) {
				// delete task;
				TL_deleteID(task->TaskID);
			}
		}
	}while(TL_pointNext());
}

void SCH_Update(void) {
	TL_pointMark();

	TL_pointStart();
	STask* task = NULL;
	do {
		task = TL_getCurrent();
		if(task->Delay == 0) {
			(task->RunMe)++;
			if(task->Period) {
				task->Delay = task->Period;
			}
		}
		else {
			(task->Delay) -= INTERRUPT_PERIOD;
		}
	}while(TL_pointNext());

	TL_restoreMark();
}

