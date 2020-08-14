@ Joel Plotnik - 006642110
@ Program to calculate the n-th Fibonacci number
@ Raspberry Pi processor definition
.cpu cortex-a53
.fpu neon-fp-armv8

@ Constant program data
.data
alert: .asciz "Overflow occurred at: %d\n"
.extern printf

@ Program code
.text
.align 2
.global main
.type main, %function
main:
    mov r4, lr      @ copy main function into r4
    mov r1, #1      @ fib(1) = 1
    mov r2, #1      @ fib(1) = 1

fib:
    adds r3, r1, r2 @ fib(n) = fib(n-1) + fib(n-2)
    mov r1, r2      @ fib(n-1) = fib(n-2)
    mov r2, r3      @ fib(n-2) = fib(n)
    bvs end
    bl fib

end:
    ldr r0, =alert  @Load string 'alert' string into r0
    bl printf       @ print "Overflow occurred at: %d\n"
    mov r0, #0      @ return 0
    mov lr, r4
    bx lr







