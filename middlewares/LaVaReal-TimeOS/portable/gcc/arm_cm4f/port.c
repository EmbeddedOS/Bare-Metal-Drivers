#include <stdint.h>

static uint32_t g_tick_count = 0;

__attribute__((naked)) void PendSV_Handler(void)
{
	/* 1. Save the context of the current task. */
	__asm volatile("MRS R0, PSP");			// Get current PSP.
	__asm volatile("STMDB R0!, {R4-R11}");  // Save stack frame 2 start from current PSP.
											// Stack frame 1 is automatically saved by
											// processor when it switch to handle mode to handle
										 	// Sys-tick exception.
											// STMDB - Store Multiple Decrement Before (Store
											// Multiple Full Descending) stores multiple registers to
											// sequential memory locations using an address
											// from a base register. `!` causing the instruction
											// to write a modified value back to R0.
											// So when we save done, the R0 will hold the current
											// PSP value.

	__asm volatile ("PUSH {LR}");			// Save LR before we Branch everywhere.
	__asm volatile("BL save_psp_value");	// Save current PSP after push stack frame 2,
											// with first argument is R0.
	/* 2. Retrieve the context of the next task. */
	__asm volatile("BL update_next_task");	// Increase the current task to next task.
	__asm volatile("BL get_psp_value");		// Get PSP value of next task and store to R0.
	__asm volatile("LDMIA R0!, {R4-R11}");  // Retrieve stack frame 2 start from PSP's next task.
											// Stack frame 1 of the next task will be retrieved
											// when exception exit automatically by processor.
	__asm volatile("MSR PSP, R0");			// Update PSP value to stack frame 1 after retrieving
											// Stack frame 2.
	__asm volatile ("POP {LR}");

	/* 3. Return to thread mode. */
	__asm volatile("BX LR");
}

void SysTick_Handler(void)
{
	/* 1. Increase global tick count. */
	g_tick_count++;

	/* 2. Pend the PendSV exception for context switching. */
	uint32_t *pICSR = (uint32_t *)0xE000ED04; // Get Interrupt Control and State Register.
	*pICSR |= (1 << 28);
}