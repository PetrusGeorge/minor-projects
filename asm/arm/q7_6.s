.data

numero:
	.asciz "11111111111111111111111111101111"

	.text
	.global _start

_start:
	ldr  r0, =numero
	ldrb r1, [r0]

	// 2^30 31 bit
	mov r2, #0x40000000

	bl to_number

	// r4 eh o valor de retorno
	mov r4, #0
	cmp r1, #0
	beq pos

	mov r4, #-1
	cmp r1, #1
	beq neg

	b ret_1

to_number:
	sub r1, #48
	bx  lr

pos:
	// iterate string
	add  r0, #1
	ldrb r1, [r0]

	// end of string
	cmp r1, #0
	beq ret_0

	bl to_number

	// not binary
	cmp r1, #0
	blt ret_1
	cmp r1, #1
	bgt ret_1

	// 0 or r2
	mul r3, r2, r1

	// bit result into r4
	add r4, r3

	// goes to next bit
	asr r2, #1
	b   pos

neg:
	// iterate string
	add  r0, #1
	ldrb r1, [r0]

	// end of string
	cmp r1, #0
	beq ret_0

	bl to_number

	// not binary
	cmp r1, #0
	blt ret_1
	cmp r1, #1
	bgt ret_1

	mov r10, #1
	sub r1, r10, r1

	// 0 or r2
	mul r3, r2, r1

	// bit result into r4
	sub r4, r3

	// goes to next bit
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
