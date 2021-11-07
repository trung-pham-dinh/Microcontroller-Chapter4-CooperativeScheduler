/*
 * Scheduler.c
 *
 *  Created on: Nov 2, 2021
 *      Author: fhdtr
 */

#include "Scheduler.h"
static const uint32_t SYS_CLK_FREQ = 16000;


static uint32_t INTERRUPT_PERIOD = 0;

void SCH_Init(TIM_HandleTypeDef *htim) {
	INTERRUPT_PERIOD = (htim->Instance->PSC+1)*(htim->Instance->ARR+1) / SYS_CLK_FREQ;
	TL_init();
}

uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD) {
	TL_insert(pFunc, DELAY, PERIOD);
	return (uint32_t)pFunc;
}

void SCH_Delete_Task(uint32_t TaskID) {
	TL_removeID(TaskID);
}

void SCH_Dispatch_Tasks(void) {
	STask* task =  TL_getFront();
	if(task && task->RunMe) {
		(*(task->pTask))();
		(task->RunMe)--;
		if(task->RunMe == 0) {
			struct Node* delNode = TL_removeFront();
			if((delNode->data).Period) {
				(delNode->data).Delay = (delNode->data).Period;
				TL_insertNode(delNode);
			}
		}
	}

	SCH_Go_To_Sleep();
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

void SCH_Go_To_Sleep(void) {
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}
