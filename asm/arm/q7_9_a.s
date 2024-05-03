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

	mov r3, #4
	mul r2, r0, r3
	ldr r1, [r11, r2]
	add r1, r1, #1
	str r1, [r11, r2]

	add r0, #1

	b for

end:
	mov r7, #1
	mov r0, #0
	swi 0

