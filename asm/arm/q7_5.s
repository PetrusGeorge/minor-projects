.data

n:
	.word 5

s:
	.word 3

COMB:
	.word 0

	.text
	.global _start

_start:
	ldr r0, =n
	ldr r0, [r0]

	ldr r1, =s
	ldr r1, [r1]

	cmp r1, r0
	bgt ret_1
	beq ret_3

	cmp r1, #0
	blt ret_2
	beq ret_4

	cmp r0, #0
	blt ret_2
	beq ret_4

	mov r3, r0
	bl  fatorial
	mov r4, r2

	mov r3, r1
	bl  fatorial
	mov r5, r2

	sub r3, r0, r1
	bl  fatorial
	mov r6, r2

	mul r5, r6

	bl divide

	mov r0, #0
	b   end

fatorial:

	mov r2, #1

fatorial_loop:
	mul r2, r3
	sub r3, #1
	cmp r3, #1
	bgt fatorial_loop

	bx lr

divide:
	push {r4, lr}
	mov  r2, #0

divide_loop:
	sub r4, r5
	add r2, #1
	cmp r4, r5
	bge divide_loop

	pop {r4, pc}

ret_1:
	mov r0, #1
	b   end

ret_2:
	mov r0, #2
	b   end

ret_3:
	mov r0, #3
	b   end

ret_4:
	mov r0, #4
	b   end

end:
	mov r7, #1
	swi 0
