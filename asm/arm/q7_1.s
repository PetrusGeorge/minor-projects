.data

a:
	.word 3

b:
	.word 4

m:
	.word 10

n:
	.word 0

	.text
	.global _start

_start:
	ldr r1, =a
	ldr r1, [r1]

	ldr r2, =b
	ldr r2, [r2]

	ldr r3, =m
	ldr r3, [r3]

	ldr r4, =n
	ldr r4, [r4]

	cmp r2, r3
	bge n_igual_m
	cmp r4, r1
	bge n_igual_m

	b n_igual_b

n_igual_m:
	ldr r0, =n
	str r3, [r0]
	b   end

n_igual_b:
	ldr r0, =n
	str r2, [r0]
	b   end

end:
	mov r7, #1
	mov r0, #0
	swi 0
