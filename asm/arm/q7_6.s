.data

numero:
	.asciz "11111111111111111111111111101111"

	.text
	.global _start

_start:
	ldr  r0, =numero
	ldrb r1, [r0]
	mov  r2, #0x40000000

	bl to_number

	mov r4, #0
	cmp r1, #0
	beq pos

	mov r4, #-1
	cmp r1, #1
	beq neg

	mov r1, #1
	b   ret_1

to_number:
	sub r1, #48
	bx  lr

pos:
	add  r0, #1
	ldrb r1, [r0]

	cmp r1, #0
	beq ret_0

	bl to_number

	cmp r1, #0
	blt ret_1
	cmp r1, #1
	bgt ret_1

	mul r3, r2, r1
	add r4, r3
	asr r2, #1
	b   pos

neg:
	add  r0, #1
	ldrb r1, [r0]

	cmp r1, #0
	beq ret_0

	bl to_number

	cmp r1, #0
	blt ret_1
	cmp r1, #1
	bgt ret_1

	mov r10, #1
	sub r1, r10, r1

	mul r3, r2, r1
	sub r4, r3
	asr r2, #1
	b   neg

ret_1:
	mov r0, #1
	b   end

ret_0:
	mov r0, #0
	b   end

end:
	mov r7, #1
	swi 0
