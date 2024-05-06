.data

A:
	.space 404

B:
	.space 404

C:
	.word 1

	.text
	.global _start

_start:
	ldr r8, =A
	ldr r9, =B

	ldr r0, =C
	ldr r7, [r10]
	mov r0, #0

	// r7 C

for:
	// i <= 100
	cmp r0, #100
	bgt end

	mov r3, #4
	mul r2, r0, r3

	// A[i]
	ldr r5, [r8, r2]

	// B[i]
	ldr r6, [r9, r2]

	// if(A[i] < B[i] && A[i] != 0)

	cmp r5, r6
	bge else
	cmp r5, #0
	bne else

	// A[i] = B[i] + C
	add r4, r6, r7

cont:

	// store result from any branch
	str r4, [r8, r2]

	// i++
	add r0, #1
	b   for

else:
	// A[i] = B[i] - C
	sub r4, r6, r7
	b   cont

end:
	mov r7, #1
	mov r0, #0
	swi 0

