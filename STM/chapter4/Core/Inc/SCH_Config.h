/*
 * SCH_Config.h
 *
 *  Created on: Nov 14, 2021
 *      Author: fhdtr
 */

#ifndef INC_SCH_CONFIG_H_
#define INC_SCH_CONFIG_H_

#define SCH_SYSCLK_FREQ 16000
#define SCH_MAX_TASKS 5
#define SCH_REPORT_FREQ 100 // each "SCH_REPORT_FREQ" times call SCH_Update() -> SCH_Report() will be call
#define SCH_PRINT_TASK_FREQ 50 // each "SCH_PRINT_TASK_FREQ" times call SCH_Update() -> SCH_Print() will be call


#endif /* INC_SCH_CONFIG_H_ */
