/*
 * Scheduler.c
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */
#include "Scheduler.h"

#define MAX_TASK	5

int hashID = 1;

static uint32_t INTERRUPT_PERIOD = 0;
static const uint32_t SYS_CLK_FREQ = 8000;


void SCH_Init(TIM_HandleTypeDef *htim) {
	INTERRUPT_PERIOD = (htim->Instance->PSC+1)*(htim->Instance->ARR+1) / SYS_CLK_FREQ;
	TL_init();
}

uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD) {
	if(TL_size() == MAX_TASK) {
		return 0;
	}

	STask* task = (STask*)malloc(sizeof(STask));
	task->pTask = pFunc;
	task->Delay = DELAY;
	task->Period = PERIOD;
	task->RunMe = 0;
	task->TaskID = hashID++;

//	TL_insertFront(task);
	TL_insertOrder(task);

	return hashID; // hashID start from 1, 0 for error
}

void SCH_Dispatch_Tasks(void) {
//	TL_pointStart();
//	STask* task = NULL;
//	do {
//		task = TL_getCurrent();
//		if(task->RunMe > 0) {
//			(*(task->pTask))();
//			(task->RunMe)--;
//			if(task->Period == 0) {
//				// delete task;
//				SCH_Delete_Task(task->TaskID);
//			}
//		}
//	}while(TL_pointNext());

	TL_pointStart();
	STask* task = TL_getCurrent();
	if(task->RunMe > 0) {
		(*(task->pTask))();
		(task->RunMe)--;
		if(task->RunMe == 0) {
			task = TL_deleteFront();
			if(task->Period) {
				task->Delay = task->Period;

				//TL_insertOrder(task);
				HAL_GPIO_TogglePin(DEBUG3_GPIO_Port, DEBUG3_Pin);
			}
		}
	}

	//SCH_Go_To_Sleep();
}

void SCH_Update(void) {
//	TL_pointMark();
//
//	TL_pointStart();
//	STask* task = NULL;
//	do {
//		task = TL_getCurrent();
//		if(task->Delay == 0) {
//			(task->RunMe)++;
//			if(task->Period) {
//				task->Delay = task->Period;
//			}
//		}
//		else {
//			(task->Delay) -= INTERRUPT_PERIOD;
//		}
//	}while(TL_pointNext());
//
//	TL_restoreMark();


	TL_pointMark();

	TL_pointStart();

	STask* task = TL_getCurrent();


	if(task) {
		if(task->Delay == 0) {
			(task->RunMe)++;
		}
		else {
			(task->Delay) -= INTERRUPT_PERIOD;
		}
	}

	TL_restoreMark();
}

unsigned char SCH_Delete_Task(const uint32_t TASK_INDEX) {
	if(TL_deleteID(TASK_INDEX)) {
		return 1;
	}
	return 0;
}

void SCH_Go_To_Sleep(void) {
	HAL_SuspendTick(); // stop the systick interrupt
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

