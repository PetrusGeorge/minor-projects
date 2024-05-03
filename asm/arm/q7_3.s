.data

input:
	.asciz "HArdwArE"

output:
	.space 10

	.text
	.global _start

_start:
	mov r10, #0
	ldr r0, =input
	ldr r1, =output

tamanho:
	ldrb r2, [r0]

	cmp r2, #0
	beq parar

	add r10, #1
	add r0, #1
	b   tamanho

parar:
	ldr r0, =input
	sub r10, #1
	add r1, r10

invert_string:
	ldrb r3, [r0]
	cmp  r3, #0
	beq  print

	cmp r3, #65
	blt not_char

	cmp r3, #90
	ble to_upper

	cmp r3, #97
	blt not_char

	cmp r3, #122
	ble to_lower

	b end

not_char:
	mov r0, #1
	b   end

to_upper:
	add r3, #32
	b   inverted_store

to_lower:
	sub r3, #32
	b   inverted_store

inverted_store:
	strb r3, [r1]
	sub  r1, #1
	add  r0, #1
	b    invert_string

print:
	mov r0, #1
	ldr r1, =output
	mov r2, r10
	add r2, #1
	mov r7, #4
	swi 0

	mov r0, #0

end:
	mov r7, #1
	swi 0
