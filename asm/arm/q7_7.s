.data

vetorx:
	.space 64

numerosDe1:
	.word 0

	.text
	.global _start

_start:
	ldr r0, =vetorx

	// r2 counts number of 1's
	mov r2, #0

	// r3 counts iterations
	mov r3, #0

loop_64:
	// for(int i = 0; i < 64; i++)
	cmp r3, #64
	bge end

	// vetorx[i]
	ldrb r1, [r0]

	// add counter if 1
	cmp  r1, #1
	bleq count

	// adds to iters
	add r0, #1
	add r3, #1

	b loop_64

count:
	add r2, #1
	bx  lr

end:
	// store result
	ldr r0, =numerosDe1
	str r2, [r0]

	mov r0, #0
	mov r7, #1
	swi 0
