/*
 * Scheduler.h
 *
 *  Created on: Nov 2, 2021
 *      Author: fhdtr
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include <stdlib.h>
#include "TaskList.h"

void SCH_Init(TIM_HandleTypeDef *htim);
uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_Delete_Task(uint32_t TaskID);
void SCH_Dispatch_Tasks(void);
void SCH_Update(void);
void SCH_Go_To_Sleep(void);

#endif /* INC_SCHEDULER_H_ */
