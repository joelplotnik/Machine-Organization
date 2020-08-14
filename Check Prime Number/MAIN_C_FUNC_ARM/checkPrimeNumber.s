@ Raspberry Pi processor definition
.cpu cortex-a53
.fpu neon-fp-armv8

@ Constant data
.data

@ Program code
.text
.align 2
.global checkPrimeNumber
.type checkPrimeNumber, %function

checkPrimeNumber:
    push {fp, lr}
	add fp, sp, #4

	@ save the input argument into non-volitile registers
	mov r7, r0

    cmp r7, #1          @ compare number in r7 to the number 1
    beq notPrime        @ if r7 is equal to 1 then branch to notPrime
    cmp r0, #2          @ compare number in r4 to the number 2
    beq prime           @ if r7 is equal to 2 then branch to prime
    mov r1, #2
    udiv r8, r7, r1     @ store value 2 in r7
    mov r2, #1          @ incrementor

modulo:
    add r2, r2, #1      @ add 1 to r2 making value in r2 = 2 for first iteration
    udiv r3, r7, r2     @ divide argument by r2
    mul r3, r3, r2      @ multiply quotient by r2
    sub r3, r7, r3      @ subtract argument by product
    cmp r3, #0          @ compare difference to 0
    beq notPrime        @ if the difference is 0 the argument is not prime
    cmp r2, r8          @ compare the incrementor (r2) to half the value of the argument
    beq prime           @ if modulo loop made it this far, the argument is prime
    b modulo            @ loop back to modulo


notPrime:
    mov r0, #0          @ return 0
    b done

prime:
    mov r0, #1          @ return 1
    b done

done:
	sub sp, fp, #4
	pop {fp, pc}
