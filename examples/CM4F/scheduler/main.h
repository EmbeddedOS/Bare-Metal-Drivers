/*
 * main.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Larva
 */

#ifndef MAIN_H_
#define MAIN_H_

/* Clock */
#define HSI_CLOCK 			16000000u
#define SYSTICK_TIM_CLOCK	HSI_CLOCK

/* Interrupt control */
#define	INTERRUPT_DISABLE() do {__asm volatile ("MOV R0, #0x1");\
								__asm volatile ("MSR PRIMASK, R0");} while(0);
#define	INTERRUPT_ENABLE() 	do {__asm volatile ("MOV R0, #0x0");\
								__asm volatile ("MSR PRIMASK, R0");} while(0);


/* Stack memory calculations */
#define SIZE_TASK_STACK		1024U
#define SIZE_SCHED_STACK	1024U

#define SRAM_START 			0x20000000U
#define SIZE_SRAM			(128 * 1024)
#define SRAM_END 			(SRAM_START + SIZE_SRAM)

#define TASK_1_STACK_START	SRAM_END
#define TASK_1_STACK_END	(TASK_1_STACK_START - SIZE_TASK_STACK)

#define TASK_2_STACK_START	TASK_1_STACK_END
#define TASK_2_STACK_END	(TASK_2_STACK_START - SIZE_TASK_STACK)

#define TASK_3_STACK_START	TASK_2_STACK_END
#define TASK_3_STACK_END	(TASK_3_STACK_START - SIZE_TASK_STACK)

#define TASK_4_STACK_START	TASK_3_STACK_END
#define TASK_4_STACK_END	(TASK_4_STACK_START - SIZE_TASK_STACK)

#define SCHED_STACK_START	TASK_4_STACK_END
#define SCHED_STACK_END		(SCHED_STACK_START - SIZE_TASK_STACK)

#define IDLE_STACK_START	SCHED_STACK_END
#define IDLE_STACK_END		(IDLE_STACK_START - SIZE_TASK_STACK)

#define USER_TASK_READY_STATE	0
#define USER_TASK_BLOCKED_STATE	1

#define MAX_TASKS 			5

void idle(void);
void task_1_handler(void);
void task_2_handler(void);
void task_3_handler(void);
void task_4_handler(void);

void init_tasks_stack(void);
void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(void);
__attribute__((naked)) void switch_to_psp(void);
void enable_system_fault_exceptions(void);
uint32_t get_psp_value(void);

typedef struct {
	  uint32_t psp_value;
	  uint32_t block_count;
	  uint8_t run_state;
	  void (*task_handler)(void);
} TCB_t;

#endif /* MAIN_H_ */
