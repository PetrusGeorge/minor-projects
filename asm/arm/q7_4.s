.data

first:
	.word 0

second:
	.word 0

result:
	.word 0

	.text
	.global _start

_start:
	ldr r0, =first
	ldr r0, [r0]

	ldr r1, =second
	ldr r1, [r1]

	mov r2, #0

	cmp r1, #0
	blt mult_neg
	bgt mult_pos

	b end

mult_pos:
	add r3, r0
	sub r1, #1

	cmp r1, #0
	beq end

	b mult_pos

mult_neg:
	sub r3, r0
	add r1, #1

	cmp r1, #0
	beq end

	b mult_neg

end:
	ldr r0, =result
	str r3, [r0]

	mov r7, #1
	mov r0, #0
	swi 0
