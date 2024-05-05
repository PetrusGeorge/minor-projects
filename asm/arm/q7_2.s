.data

a:
	.word 10

b:
	.word 25

x:
	.word 0

	.text
	.global _start

_start:
	// a = ...
	ldr r0, =a
	ldr r0, [r0]

	// b = ...
	ldr r1, =b
	ldr r1, [r1]

	// x = 0
	ldr r2, =x
	ldr r2, [r2]

	// a < 0
	cmp r0, #0
	blt end

	// b > 50
	cmp r1, #50
	bgt end

	// x = 1
	mov r2, #1
	ldr r3, =x
	str r2, [r3]

end:
	mov r7, #1
	mov r0, #0
	swi 0

