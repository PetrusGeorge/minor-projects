.data

A:
	.space 40

	.text
	.global _start

_start:
	ldr r11, =A
	mov r0, #0

for:
	cmp r0, #10
	bge end

	and r1, r0, #1
	cmp r1, #0
	beq par
	bne impar

par:
	mov r2, #4
	mul r3, r0, r2
	ldr r1, [r11, r3]

	add r2, r3, #4
	ldr r2, [r11, r2]

	add r1, r2

	b cont

impar:
	mov r2, #4
	mul r3, r0, r2
	ldr r1, [r11, r3]

	mov r2, #2
	mul r1, r2

	b cont

cont:
	str r1, [r11, r3]
	add r0, #1
	b   for

end:
	mov r7, #1
	mov r0, #0
	swi 0

