@ Joel Plotnik - 006642110
@ Program to find prime numbers between two positive integers
@ Raspberry Pi processor definition
.cpu cortex-a53
.fpu neon-fp-armv8

@ Constant data
.data
.extern printf
.extern scanf

prompt: .asciz "Enter two positive integers: "
inp1: .asciz "%d"
inp2: .asciz "%d "
primenums: .asciz "Prime numbers between %d and %d are: "

@ Program code
.text
.align 2
.global main
.type main, %function

main:
    push {fp, lr}       @ push lr and fp to the stacks
    add fp, sp, #4      @ move sp down 4 bytes from frame pointer

    ldr r0, =prompt     @ display prompt
    bl printf

    ldr r0, =inp1       @ get first number
    mov r1, sp
    bl scanf
    ldr r4, [sp]

    ldr r0, =inp1       @ get second number
    mov r1, sp
    bl scanf
    ldr r5, [sp]

    mov r1, r4          @ display the user numbers and set up program to print prime numbers
    mov r2, r5
    ldr r0, =primenums
    bl printf

    add r6, r4, #0      @ set r6 equal to first number and use r6 as an incrementor

loop:
    add r6, r6, #1      @ add 1 to r6
    mov r0, r6          @ move r6 to r0
    bl checkPrimeNumber @ pass num in r0 to checkPrimeNumber
    cmp r0, #1          @ if function return value is 1
    beq print           @ print prime num
    cmp r6, r5          @ compare first number to the second number
    beq done            @ if r6 = r5 branch to done
    b loop              @ branch back to loop

print:
    mov r1, r6          @ move prime number to r0
    ldr r0, =inp2
    bl printf
    cmp r6, r5          @ compare first number to the second number
    beq done            @ if r6 = r5 branch to done
    b loop              @ branch back to loop

done:
    sub fp, #4
    pop {fp, pc}
