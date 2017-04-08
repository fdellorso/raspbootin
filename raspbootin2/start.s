.section ".init"

// Make Start global.
.globl Start
.global PUT32
.global GET32
.global dummy
.global BOOTUP

/**
 * from the original raspbootin
 **/
start:
	// Setup the stack.
	mov	sp, #0x8000
	bl main

	// we're loaded at 0x8000, relocate to _start.
/*.relocate:
	// copy from r3 to r4.
	mov	r3, #0x8000
	ldr	r4, =_start
	ldr	r9, =_data_end
1:
	// Load multiple from r3, and store at r4.
	ldmia	r3!, {r5-r8}
	stmia	r4!, {r5-r8}

	// If we're still below file_end, loop.
	cmp	r4, r9
	blo	1b

	// Clear out bss.
	ldr	r4, =_bss_start
	ldr	r9, =_bss_end
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r8, #0
1:
	// store multiple at r4.
	stmia	r4!, {r5-r8}

	// If we're still below bss_end, loop.
	cmp	r4, r9
	blo	1b*/

	// Call kernel_main


	// halt
halt:
	wfe
	b halt


PUT32:
    str r1,[r0]
    mov pc, lr

GET32:
    ldr r0,[r0]
    mov pc, lr

dummy:
    mov pc, lr
    
BOOTUP:
    mov pc, r0
    b halt
