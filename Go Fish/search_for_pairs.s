.cpu cortex-a53
.fpu neon-fp-armv8

.data

.text
.align 2
.global search_for_pairs
.type search_for_pairs, %function

search_for_pairs:
	push {fp, lr}          @ push lr, fp (calling function) onto stack, updates sp by -8
    	add fp, sp, #4         @ point fp (this function) to lr on stack @ -4

    @ r0 contains array

	mov r1, #1 	@ address counter
	mov r2, #4	@ multiplier
	mov r3, #0	@ pair counter

check_pair_loop:
	cmp r2, #56		        @ compare r2 to the last index of array
	beq check_pair_done	    @ branch to end of function
	mov r4, r2		        @ use r4 to store index value mulitplier
	mul r1, r1, r2		    @ first it = 4
	add r1, r1, r0		    @ first it = index 1
	ldr r2, [r1]		    @ load the value in address into r2
	cmp r2, #2		        @ compare value at index[i] to 2
	bge calc_pair		    @ branch to calculate pair

	mov r1, #1		        @ reset r1 to 1
	mov r2, r4		        @ set r2 to index value
	add r2, r2, #4		    @ add 4 to move to next index value
	b check_pair_loop

calc_pair:
	cmp r2, #4		        @ compare index value to #4
	bge calc_two_pairs	    @ branch to calculate two pairs
	add r3, r3, #1		    @ add 1 point

	@ subtract total cards taken from player/ cpu
	ldr r2, [r0]		    @ put element array[0] (cards in hand) into r2
	sub r2, r2, #2		    @ r2 = array[0] (cards in hand) - one pair
	str r2, [r0]		    @ put result back into array[0]

	@ update the count for particular card rank
	ldr r2, [r1]		    @ put element array[i] into r2
	sub r2, r2, #2		    @ r2 = arra[i] - one pair
	str r2, [r1]		    @ put result back into array[i]

	mov r1, #1		        @ reset r1 to 1
	mov r2, r4		        @ set r2 to index value
	add r2, r2, #4		    @ add 4 to move to next index value
	b check_pair_loop


calc_two_pairs:
	add r3, r3, #2

	@ subtract total cards taken from player/ cpu
	ldr r2, [r0]		@ put element array[0] (cards in hand) into r2
	sub r2, r2, #4		@ r2 = array[0] (cards in hand) - one pair
	str r2, [r0]		@ put result back into array[0]

	@ update the count for particular card rank
	ldr r2, [r1]
	sub r2, r2, #4
	str r2, [r1]

	mov r1, #1		@ reset r1 to 1
	mov r2, r4		@ set r2 to index value
	add r2, r2, #4		@ add 4 to move to next index value
	b check_pair_loop

check_pair_done:
	mov r0, r3		@ return value
	b endFunction

endFunction:
    sub sp, fp, #4         @ place sp at -8 on stack
    pop {fp, lr}           @ pop fp (calling function), pop lr, set sp at 0 on stack
    bx lr                  @ branch back to calling function











