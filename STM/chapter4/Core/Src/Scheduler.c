/*
 * Scheduler.c
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */
#include "Scheduler.h"
static const uint32_t SYS_CLK_FREQ = 8000;


static uint32_t INTERRUPT_PERIOD = 0;


static uint32_t hashID = 0;

void SCH_Init(TIM_HandleTypeDef *htim) {
	INTERRUPT_PERIOD = (htim->Instance->PSC+1)*(htim->Instance->ARR+1) / SYS_CLK_FREQ;
	TL_init();
}

uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD) {
	STask* task = (STask*)malloc(sizeof(STask));
	task->pTask = pFunc;
	task->Delay = DELAY;
	task->Period = PERIOD;
	task->RunMe = 0;
	task->TaskID = hashID++;

	TL_insert(task);
	return hashID;
}

void SCH_Dispatch_Tasks(void) {
	STask* task =  TL_getFront();
	if(task && task->RunMe) {
		(*(task->pTask))();
		(task->RunMe)--;
		if(task->RunMe == 0) {
			task = TL_removeFront();
			if(task->Period) {
				task->Delay = task->Period;
				TL_insert(task);
			}
		}
	}
}

void SCH_Update(void) {
	STask* task = TL_getFront();
	if(task) {
		if(task->Delay == 0) {
			task->RunMe++;
		}
		else {
			task->Delay -= INTERRUPT_PERIOD;
		}
	}
}
