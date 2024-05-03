.data

hello:
	.asciz "Hello World\n"

	len = . - hello

	.text
	.global _start

_start:
	mov r0, #1
	ldr r1, =hello
	ldr r2, =len
	mov r7, #4
	swi 0

	mov r7, #1
	mov r0, #0
	swi 0
