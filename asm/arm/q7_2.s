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
	ldr r0, =a
	ldr r0, [r0]
	ldr r1, =b
	ldr r1, [r1]
	ldr r2, =x
	ldr r2, [r2]
	ldr r3, =x

	cmp r0, #0
	blt end

	cmp r1, #50
	bgt end

	mov r2, #1

end:
	str r2, [r3]
	mov r7, #1
	mov r0, #0
	swi 0

