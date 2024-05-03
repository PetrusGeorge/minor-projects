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
	ldr r11, =A
	ldr r12, =B
	ldr r13, =C
	ldr r7, [r13]
	mov r0, #0

	@r5 A i
	@r6 B i
	@r7 C

for:
	cmp r0, #100
	bgt end

	mov r3, #4
	mul r2, r0, r3

	ldr r5, [r11, r2]
	ldr r6, [r12, r2]

	cmp r5, r6
	bge else
	cmp r5, #0
	beq else

    add r4, r6, r7

cont:

	str r4, [r11, r2]
	add r0, #1
	b   for

else:
    sub r4, r6, r7
    b cont

end:
	mov r7, #1
	mov r0, #0
	swi 0

