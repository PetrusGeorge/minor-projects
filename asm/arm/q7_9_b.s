.data

A:
	.space 40

	.text
	.global _start

_start:
	ldr r11, =A

	// r0 is iter counter
	mov r0, #0

for:
	// i < 10
	cmp r0, #10
	bge end

	// i % 2
	and r1, r0, #1
	cmp r1, #0
	beq pair
	bne odd

pair:
	// A[i]
	mov r2, #4
	mul r3, r0, r2
	ldr r1, [r11, r3]

	// A[i + 1]
	add r2, r3, #4
	ldr r2, [r11, r2]

	// A[i] + A[i + 1]
	add r1, r2

	b cont

odd:
	// A[i]
	mov r2, #4
	mul r3, r0, r2
	ldr r1, [r11, r3]

	// A[i] * 2
	mov r2, #2
	mul r1, r2

	b cont

cont:
	// load result from any of the branches
	str r1, [r11, r3]
	add r0, #1
	b   for

end:
	mov r7, #1
	mov r0, #0
	swi 0

