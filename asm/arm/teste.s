.text
.global _start

_start:
	mov r0, #5
	mov r1, #7

	mov r4, #20
	mov r5, #20
	mov r6, #20
	mov r7, #20

	bl  add_numbers

	mov r7, #1
	mov r0, #0
	swi 0

add_numbers:

	push {r4-r11, lr}
    mov fp, sp
    sub sp, #64

    mov r1, #100
    str r1, [fp, #-4]

    ldr r2, [fp, #-4]

	mov r4, #0
	mov r5, #0
	mov r6, #0
	mov r7, #0
    mov sp, fp
	pop  {r4-r11, pc}
