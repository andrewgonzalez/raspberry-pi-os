#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, bssinit         // Clear bss with proc 0
	b	master

proc_hang: 
	b 	proc_hang

bssinit:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

master:
	mrs x0, mpidr_el1       // Get proc ID again
	and x0, x0, #0xFF
	mov x1, #0x1000         // 4Kb stack size
	mov x2, #LOW_MEMORY
	madd x1, x0, x1, x2      // multiply stack size and proc id, then add low memory
	mov	sp, x1
	bl	kernel_main
	b 	proc_hang		    // other procs may get this far, then hang
