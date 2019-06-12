#include "arm/sysregs.h"

#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang:
	wfe
	b 	proc_hang

master:
	ldr	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1, x0

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0

	ldr	x0, =SCR_VALUE
	msr	scr_el3, x0

	ldr	x0, =SPSR_EL2VALUE
	msr	spsr_el3, x0

	adr	x0, el2_entry
	msr	elr_el3, x0

	eret				

el2_entry:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #LOW_MEMORY   // I think this is the SP_EL2 stack pointer
	bl	kernel_init

	ldr x0, =SPSR_EL1VALUE
	msr spsr_el2, x0
	adr x0, kernel_entry     // enter kernel at EL1
	msr elr_el2, x0

	eret

kernel_entry:
	mov x0, #LOW_MEMORY
	add x0, x0, #0x1000   // advance stack pointer 4kb so I don't overwrite data pointed at by SP_EL2
	mov sp, x0            // This is the SP_EL1 stack pointer, so it needs to be set
	bl  kernel_main
	b 	proc_hang         // should never come here
