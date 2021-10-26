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
#include "TaskList.h"

void SCH_Init(TIM_HandleTypeDef *htim);
uint32_t SCH_Add_Task(void(*pFunc)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_Dispatch_Tasks(void);
void SCH_Update(void);

#endif /* INC_SCHEDULER_H_ */
