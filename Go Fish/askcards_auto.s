.cpu cortex-a53
.fpu neon-fp-armv8

.data
output: .asciz "\nGo Fish Computer\n"
ask: .asciz "CPU asks for a %d\n"

.text

.align 2
.global askcards_auto
.type askcards_auto, %function

askcards_auto:
    push {fp, lr}
    add fp, sp, #4

    @r0contains file pointer
    @r1 contains cpu array
    @r2 contains player array

    mov r4, r0                @ place file pointer in r4
    mov r5, r1                @ place cpu array address in r5
    mov r6, r2                @ place player array address in r6

    mov r0, #0                @ place seed to randomize
    bl time
    bl srand

    @ loop randomly chooses a memory location among the available memory slots
    @ in the cpu array to select a card for the purpose of checking to see if
    @ player has the same card

    whileLoop1:
        bl rand               @ place a random number output in r0
        mov r1, #13
        bl modulo             @ r0 % r1 ->  random number % card count in cpu array (e.g.,0-5)
                              @ random number should be between 1 - 13 after modulo             ??????
        add r0, r0, #1
        mov r9, r0

        mov r3, #4
        mul r3, r9, r3        @ multiply the random number by 4 to get proper memory location

        @ check to see if there are any cards in that memory location, if not, then try again
        add r3, r3, r5        @ add the random number (multiple of 4) to the address of cpu array
        ldr r9, [r3]          @ place number of cards at random memory location (4 * (1-13) + cpu array) into r9
        cmp r9, #0            @ compare that number with 0
        beq whileLoop1        @ if 0 meaning no cards of that rank in hand, then reloop until
                              @ random memory spot in cpu array is chosen with cards of that rank

        mov r7, r0            @ place number at random memory location (4 * (1-13) + p2array) into r7         ?????shouldn't r9 be 4 * (1-13)????


    mov r1, r7               @ mov random number to r1 to print
    ldr r0, =ask             @ load string "CPU asks for a %d\n" into arg reg r0
    bl printf                @ display above string

    @ check to see if player array contains cards at the same memory location relative to player array address player[0]
    mov r3, #4                @ mul operation requires number in register instead of immediate value
    mul r3, r7, r3            @ multiply (r3 = 4 * random number (1-13)))
    add r3, r3, r6            @ r3 = player array address
    ldr r2, [r3]              @ place card count number in player array memory location into r2

    cmp r2, #0                @ check to see if player array has any cards in that memory location
    beq cpuGoFish             @ if not, then go fish until card is chosen with memory location

    @ cpu chose a card in your deck so no Go Fish, cpu takes one card of that rank and places it in its deck
    sub r1, r2, #1            @ put card rank number - 1 in r1
    str r1, [r3]              @ store the new number in array address that r3 points to in player array

    @ subtract cards taken from player total cards count
    ldr r8, [r6]              @ put element player[0] (total player hand count) into r8
    sub r8, r8, #1            @ r8 = player[0] (total player hand count) + one card taken from player of that rank
    str r8, [r6]              @ put result into player[0] (total player hand count)

    @ go back to same address in cpu array and add card taken from player array to cpu array
    mov r3, #4                @ put 4 in r3
    mul r3, r3, r7            @ r3 = 4 * random number (1-13) for memory storage
    add r3, r3, r5            @ r3 = (r * random number (1-13)) + address of cpu address
    ldr r8, [r3]              @ put cpu[card rank location] into r8

    @ add count from player to cpu of same rank
    add r8, r8, #1            @ r8 = cpu[card rank location] + one card taken from player of that rank
    str r8, [r3]              @ put result back into cpu[card rank location]

    @ increase total count in cpu hand
    ldr r8, [r5]              @ put cpu[0] (total cpu card count in hand) into r8
    add r8, r8, #1            @ r8 = cpu[0] (total cpu card count in hand) + all cards taken from player of that rank
    str r8, [r5]              @ put result back into cpu[0] (total cpu card count in hand)

    mov r0, r5
    bl search_for_pairs
    b endFunction

@ cpu checked card from player based upon cards in cpu hand and player did not have any of those cards
@ so cpu had to Go Fish, which means to draw a card in its own deck and increment number of cards at cpu
@ array location

cpuGoFish:
    ldr r0, =output           @ load string "Go Fish\n" into arg reg r0
    bl printf                 @ display above string
    mov r0, r4                @ put fptr into r0
    mov r1, r5                @ put cpu array address into r1
    bl draw                   @ draw another card and add to count at proper memory location in cpu array
    mov r0, r5                @ i = 1;
    bl search_for_pairs
    b endFunction


endFunction:
    sub sp, fp, #4            @ place sp at -8 on stack
    pop {fp, lr}              @ pop fp (calling function), pop lr, set sp at 0 on stack
    bx lr                     @ branch back to calling function
