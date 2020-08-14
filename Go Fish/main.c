/*Joel Plotnik - 006642110
GO FISH */


#include <stdio.h>
#include <stdlib.h>
extern FILE * shuffle (FILE * fptr);
extern void dealcards(FILE * fptr, int arr[]);
extern int search_for_pairs(int arr[]);
extern int askcards_man(FILE * fptr, int arrPlayer[], int arrCPU[]);
extern int askcards_auto(FILE * fptr, int arrCPU[], int arrPlayer[]);
void displayPlayerHand(int arr[]);
void displayCPUHand(int arr[]);

int main(int argc, char *argv[])
{
    int pair;                   // used to check for pair
    int turn = 1;               // turn counter
    int playerPairs = 0;        // accumulate player pairs
    int cpuPairs = 0;           // accumulate cpu pairs
    int player[14], cpu[14];    //index 0 to track card count, 1-13 to track pairs

    // Create file to document plays
    FILE *out_file;
    out_file = fopen("gofish_plays.txt", "w");

    // if file not created then exit
    if(out_file == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < 14; ++i)
    {
        player[i] = 0;     // set total cards for player at 0
        cpu[i] = 0;        // set total cards for cpu at 0
    }

    FILE * fptr;
    if (argc > 1)                     // if file name indicated in main parameters
    {
        fptr = fopen(argv[1], "w");   // opens file indicated by filename in main parameter
    }
    else                              // if file name not indicated in main parameters
    {
        fptr = fopen("deck.dat", "w"); // open and set to write mode "deck.dat"
    }

    // place random number between 0-13 for card rank and place into file 52 times to represent a card deck
    shuffle(fptr);


    if (argc > 1)                      // if file name indicated in main parameters
    {
        fptr = fopen(argv[1], "r");    // opens file indicated by filename in main parameter
    }
    else                               // if file name not indicated in main parameters
    {
        fptr = fopen("deck.dat", "r"); // open and set to write mode "deck.dat"
    }


//*************************************************************************
    dealcards(fptr, player);          // deal 5 cards to player
    player[0] = 5;                    // set total card count for player to 5

    playerPairs = search_for_pairs(player);

    // FOR DEBUGGING
    //printf("player has this many pairs %d\n", playerPairs);
    //displayPlayerHand(player);

    dealcards(fptr, cpu);             // deal 5 cards to cpu
    cpu[0] = 5;                       // set total card count for cpu to 5

    cpuPairs = search_for_pairs(cpu); // search for pairs

    // FOR DEBUGGING
    //printf("cpu has this many pairs %d\n", cpuPairs);
    //displayCPUHand(cpu);


        // display first turn information
        printf("\t\tTurn: %d\n\n", turn);
        printf("\t\tPoints\n");
        printf("\tPlayer1: %d \n\tComputer: %d\n\n", playerPairs, cpuPairs);
        printf("Your hand:\n");
        for (int i = 1; i < 14; i++)
        {
            if (player[i] > 0)
            {
                printf("[%d]x%d ", i, player[i]);
            }
        }

        printf("\n\n");
        printf("Computer has %d card(s)\n\n", cpu[0]);

//************************************************************************
        // Print first turn info to file
        fprintf(out_file, "Player1 and CPU Turn 1\n");
        fprintf(out_file, "Player1 has %d pair(s).\n", playerPairs);
        fprintf(out_file, "CPU has %d pair(s).\n", cpuPairs);

        if(playerPairs > cpuPairs)
        {
            fprintf(out_file, "Eventual winner: Player1\n\n");
        }
        else if(playerPairs < cpuPairs)
        {
            fprintf(out_file, "Eventual winner: CPU\n\n");
        }
        else if(playerPairs == cpuPairs)
        {
            fprintf(out_file, "Eventual winner: Unknown\n\n");
        }
        fprintf(out_file, "\n\n");


//************************************************************************

    // play Go Fish
    while(1)   // while loop runs until winner is declared which breaks the while loop
    {
        turn++;

        // have player ask CPU for cards in its deck, if no card, then Go Fish for player (draw a card),
        pair = askcards_man(fptr, player, cpu); //return winner; 0 no winner, 1 means player 1 won, 2 means cpu won


        // replenish player deck if he/she runs out of cards
        if(cpu[0] == 0)
        {
            dealcards(fptr, cpu);
            cpu[0] = 5;
        }
        // replenish cpu deck if it runs out of cards
        if(player[0] == 0)
        {
            dealcards(fptr, player);
            player[0] = 5;
        }

        // wait for user to push ENTER
        while(getchar() != '\n');
        printf("\nPress <ENTER> to continue...\n");
        getchar();
        system("clear");

        // increase the amount of pairs player1
        playerPairs += pair;

        ////////////// FOR DEBUGGING ///////////////
        //displayPlayerHand(player);
        //displayCPUHand(cpu);

        // display the turn and how many points each player has
        printf("\t\tTurn: %d\n\n", turn);
        printf("\t\tPoints\n");
        printf("\tPlayer1: %d \n\tComputer: %d\n\n", playerPairs, cpuPairs);

        // display the cards currently in user hand
        printf("Your hand:\n");
        for (int i = 1; i < 14; i++)
        {
            if (player[i] > 0)
            {
                printf("[%d]x%d ", i, player[i]);
            }
        }

        // display the amount of cards in cpu hand
        printf("\n\n");
        if (cpu[0] != 0 )
        {
            printf("Computer has %d card(s)\n\n", cpu[0]);
        }
        else
        {
            printf("Computer has 5 card(s)\n\n");
        }


        //*******************************************************
        // print info to file
        fprintf(out_file, "Player1 Turn %d\n", turn);
        fprintf(out_file, "Player1 has %d pair(s).\n", playerPairs);
        fprintf(out_file, "CPU has %d pair(s).\n", cpuPairs);

        if(playerPairs > cpuPairs)
        {
            fprintf(out_file, "Eventual winner: Player1\n\n");
        }
        else if(playerPairs < cpuPairs)
        {
            fprintf(out_file, "Eventual winner: CPU\n\n");
        }
        else if(playerPairs == cpuPairs)
        {
            fprintf(out_file, "Eventual winner: Unknown\n\n");
        }

        fprintf(out_file, "\n\n");

        if (playerPairs >= 13)
        {
            fprintf(out_file, "\nPlayer1 won the game.\n");
        }
        if (cpuPairs >= 13)
        {
            fprintf(out_file, "\CPU won the game.\n");
        }
        if (cpuPairs == 13 && playerPairs == 13)
        {
            fprintf(out_file, "\nTie game!!\n");
        }

        //*******************************************************


        if (playerPairs >= 13)
        {
            printf("\nCongratulations, you won the game!\n");
            break;
        }
        if (cpuPairs >= 13)
        {
            printf("\nSorry, you lost. The CPU won the game.\n");
            break;
        }
        if (cpuPairs == 13 && playerPairs == 13)
        {
            printf("\n Tie game!!\n");
            break;
        }


//******************************************************************************
        // have CPU ask player for a card based on random selection from its own deck, if player doesn't have a card, Go Fish for CPU


        pair = askcards_auto(fptr, cpu, player);

        printf("\nPress <ENTER> to continue...\n");
        getchar();
        system("clear");

        cpuPairs += pair;

        ///////////// FOR DEBUGGING ///////////////
        //displayPlayerHand(player);
        //displayCPUHand(cpu);

        printf("\t\tCPU Turn: %d\n\n", turn);
        printf("\t\tPoints\n");
        printf("\tPlayer1: %d \n\tComputer: %d\n\n", playerPairs, cpuPairs);

        // display cards currently in user hand
        printf("Your hand:\n");
        for (int i = 1; i < 14; i++)
        {
            if (player[i] > 0)
            {
                printf("[%d]x%d ", i, player[i]);
            }
        }

        // Display the amount of cards in cpu hand
        printf("\n\n");
        if (cpu[0] != 0 )
        {
            printf("Computer has %d card(s)\n\n", cpu[0]);
        }
        else
        {
            printf("Computer has 5 card(s)\n\n");
        }

        //*******************************************************
        // Print info to file
        fprintf(out_file, "CPU Turn %d\n", turn);
        fprintf(out_file, "Player1 has %d pair(s).\n", playerPairs);
        fprintf(out_file, "CPU has %d pair(s).\n", cpuPairs);

        if(playerPairs > cpuPairs)
        {
            fprintf(out_file, "Eventual winner: Player1\n\n");
        }
        else if(playerPairs < cpuPairs)
        {
            fprintf(out_file, "Eventual winner: CPU\n\n");
        }
        else if(playerPairs == cpuPairs)
        {
            fprintf(out_file, "Eventual winner: Unknown\n\n");
        }

        fprintf(out_file, "\n\n");

        if (playerPairs >= 13)
        {
            fprintf(out_file, "\nPlayer1 won the game.\n");
        }
        if (cpuPairs >= 13)
        {
            fprintf(out_file, "\CPU won the game.\n");
        }
        if (cpuPairs == 13 && playerPairs == 13)
        {
            fprintf(out_file, "\nTie game!!\n");
        }

        //*******************************************************

        if (playerPairs >= 13)
        {
            printf("\nCongratulations, you won the game!\n");
            break;
        }
        if (cpuPairs >= 13)
        {
            printf("\nSorry, you lost. The CPU won the game.\n");
            break;
        }
        if (cpuPairs == 13 && playerPairs == 13)
        {
            printf("\n Tie game!!\n");
            break;
        }

    }

    fclose(out_file);
    fclose(fptr);

    return 0;
}

// for FOR DEBUGGING
void displayPlayerHand(int arr[])
{
        printf("player deck:  ");
        for (int i = 0; i < 14; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");


}

void displayCPUHand(int arr[])
{

        printf("cpu deck:     ");
        for (int i = 0; i < 14; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");


}
