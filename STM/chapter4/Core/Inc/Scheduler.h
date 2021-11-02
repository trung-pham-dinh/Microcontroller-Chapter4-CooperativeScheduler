/*
 * Scheduler.h
 *
 *  Created on: Oct 26, 2021
 *      Author: fhdtr
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include "TaskList.h"
#include "uart_printf.h"

typedef enum {
	ERROR_SCH_TOO_MANY_TASKS,
	ERROR_SCH_CANNOT_DELETE_TASK,
} SCH_ERROR;


void SCH_Init(TIM_HandleTypeDef *htim);
uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD);
unsigned char SCH_Delete_Task(const uint32_t TASK_INDEX);
void SCH_Dispatch_Tasks(void);
void SCH_Update(void);
void SCH_Go_To_Sleep(void);

#endif /* INC_SCHEDULER_H_ */
