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

	// A[i]
	mov r3, #4
	mul r2, r0, r3    // r2 is the shift in words of i
	ldr r1, [r11, r2]

	// Adds 1 to A[i]
	add r1, r1, #1
	str r1, [r11, r2]

	// i++
	add r0, #1

	b for

end:
	mov r7, #1
	mov r0, #0
	swi 0

