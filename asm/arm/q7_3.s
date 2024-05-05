.data

input:
	.asciz "HArdwArE"
	len    = . - input

output:
	.space 10

	.text
	.global _start

_start:

	// r0 endereco de entrada
	ldr r0, =input

	// r1 point to last space of output
	ldr r1, =output
	ldr r3, =len
	add r1, r3
	sub r1, #1

	// \0 on last space
	mov  r10, #0
	strb r10, [r1]
	sub  r1, #1

invert_string:
	ldrb r3, [r0]
	cmp  r3, #0
	beq  print

	// char < 'a'
	cmp r3, #65
	blt not_char

	// char <= 'z'
	cmp r3, #90
	ble to_upper

	// char < 'A'
	cmp r3, #97
	blt not_char

	// char >= 'A' && char <= 'Z'
	cmp r3, #122
	ble to_lower

	b end

not_char:
    //return 1
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
	ldr r3, =len
	mov r2, r3
	mov r7, #4
	swi 0

	// return 0
	mov r0, #0

end:
	mov r7, #1
	swi 0
