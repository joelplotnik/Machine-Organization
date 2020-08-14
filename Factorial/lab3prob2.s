@ Joel Plotnik - 006642110
@ Program to calculate the factorial of an interger value inputted by the user
@ Raspberry Pi processor definition
.cpu cortex-a53
.fpu neon-fp-armv8

@ Constant program data
.data
inp: .asciz "%d"
prompt: .asciz "Enter an integer: "
goodalert: .asciz "The value of the factorial is: %d\n"
badalert: .asciz "Overflow occurres at: %d\n"
.extern printf
.extern scanf

@ Program Code
.text
.align 2
.global main
.type main, %function
main:
    mov r4, lr
    ldr r0, =prompt     @ load 'prompt' into r0
    bl printf           @ print 'prompt'
    ldr r0, =inp        @ load 'inp' into r0
    mov r1, sp          @ move the stack pointer to r1
    bl scanf            @ scan user input into stack
    ldr r5, [sp]        @ derefenced value in stack is stored in r5
    sub r1, r5, #1      @ r1 = r5 - 1
    mov r3, r5          @ r2 = r5

factorial:
    umull r3, r2, r3, r1    @ r3 = r3 * r1 (If overflow occurs it will appear in r2)
    cmp r2, #0              @ compare r2 to zero
    bgt endtwo              @ if r2 is greater than zero, overflow occured
    sub r1, r1, #1          @ r1 = r1 - 1
    cmp r1, #0              @ compare r1 to zero
    beq endone              @ if r1 is equal to zero factorial sequence is complete, branch to endone
    bl factorial            @ loop back to factorial

endone:
    mov r1, r3          @ move the value in r3 to r1
    ldr r0, =goodalert  @ load 'goodalert' into r0
    bl printf           @ print "The value of the factorial is %d\n"
    mov r0, #0          @ return 0
    mov lr, r4
    bx lr

endtwo:
    mov r1, r5          @ move the user input value in r5 to r1
    ldr r0, =badalert   @ load 'badalert' into r0
    bl printf           @ print "Overflow occurres at: %d\n"
    mov r0, #0          @ return 0
    mov lr, r4
    bx lr
























