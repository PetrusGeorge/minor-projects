.data

vetorx:
	.space 64

numerosDe1:
	.word 0

	.text
	.global _start

_start:
	ldr r0, =vetorx
	mov r2, #0
	mov r3, #64

loop_64:
	cmp r3, #0
	beq end

	ldrb r1, [r0]

	cmp r1, #1
	bne continua
	bl  adiciona

continua:
	add r0, #1
	sub r3, #1

	b loop_64

adiciona:
	add r2, #1
	bx  lr

end:
	mov r7, #1
	mov r0, #0
	swi 0
