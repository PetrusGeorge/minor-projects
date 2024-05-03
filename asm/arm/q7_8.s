.data

input:
	.asciz "Sobstitoi"
	len    = . - input

x:
	.ascii "o"

y:
	.ascii "u"

	.text
	.global _start

_start:
	ldr r0, =input

	ldr  r2, =x
	ldrb r2, [r2]
	ldr  r3, =y
	ldrb r3, [r3]
	b    procura

substitui:
	strb r3, [r0]
	add  r0, #1
	b    procura

procura:
	ldrb r1, [r0]

	cmp r1, #0
	beq end

	cmp r1, r2
	beq substitui
	add r0, #1

	b procura

end:
	mov r0, #1
	ldr r1, =input
	ldr r2, =len
	mov r7, #4
	swi 0

	mov r7, #1
	mov r0, #0
	swi 0
