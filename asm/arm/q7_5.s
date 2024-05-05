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
	// load n
	ldr r0, =n
	ldr r0, [r0]

	// load s
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

	// n!
	mov r3, r0
	bl  fatorial
	mov r4, r2

	// s!
	mov r3, r1
	bl  fatorial
	mov r5, r2

	// (n - s)!
	sub r3, r0, r1
	bl  fatorial
	mov r6, r2

	// s! * (n - s)!
	mul r5, r6

	// n! / (s! * (n - s)!)
	bl divide

	// return 0
	mov r0, #0
	b   end

/*
int fatorial(int a){
    return a * fatorial(a-1);
}
*/
fatorial:
	push {fp, lr}

	// store r3 on stack
	mov fp, sp
	sub sp, #4
	str r3, [fp, #-4]

	// r3 == 0 => return 1
	cmp   r3, #0
	moveq r2, #1
	beq   return_fat

	// return n * fatorial(n-1)
	sub r3, #1
	bl  fatorial

	// load local n
	ldr r3, [fp, #-4]

	mul r2, r3

return_fat:
	mov sp, fp
	pop {fp, pc}

divide:
	push {r4-r5, lr}
	mov  r2, #0

divide_loop:
	sub r4, r5
	add r2, #1
	cmp r4, r5
	bge divide_loop

	pop {r4-r5, pc}

ret_1: // n < s
	mov r0, #1
	b   end

ret_2: // n < 0 || s < 0
	mov r0, #2
	b   end

ret_3: // n == s
	mov r0, #3
	b   end

ret_4: // n == 0 || s == 0
	mov r0, #4
	b   end

end:
	mov r7, #1
	swi 0
