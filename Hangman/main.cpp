/* Joel Plotnik - SI: 006642110
   CSIS 212 : Machine Organization & Assembly Language
   Duy Nguyen, Ph.D. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXIMUMWORDS 3000 // maximum amount of words to be read in
#define MAXIMUMWORDLENGTH 60 // maximum word length to be read in

int main()
{
	// seed the time
	srand(time(NULL));

	// array to store word list
	char guessWords[MAXIMUMWORDS][MAXIMUMWORDLENGTH];
	int wordsReadIn = 0; // track words read in from text file

	FILE *pToFile = fopen("dictionary.txt", "r"); // open and read file

	if(pToFile == NULL) // dictionary.txt does not exist
	{
		printf("Failed to open file.\n");
		return 0;
	}

	// var to read input from each line in text file
	char input[60];

	// store from text file into input array
	while(fgets(input, 59, pToFile))
	{
		sscanf(input, "%s", guessWords[wordsReadIn]);
	//	printf("Scanned: input:%s guessWords[%d]: %s\n", input, wordsReadIn, guessWords[wordsReadIn]);
		wordsReadIn++;
	}

	//printf("Total words read in: %d\n", wordsReadIn);

	fclose(pToFile); // close file

	// index for random word.
	int randomIndex = rand() % wordsReadIn;

	int numLives = 7; // amount of guesses/ letters in HANGMAN
	int numCorrect = 0; // how many guesses are correct
	int oldCorrect = 0; // var to dock a life

	// length of selected word
	int lengthOfWord = strlen(guessWords[randomIndex]);

	// keep track of letters guessed correctly
	int letterGuessed[60] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,};

	int quit = 0; // to break out of game loop

	// index for looping
	int loopIndex = 0;
	char guess[16]; // user guess
	char letterEntered; // store letter entered by user

	/*printf("guessWords:%s randomIndex:%d lengthOfWords:%d\n\n",
	guessWords[randomIndex],
	randomIndex,
	lengthOfWord); */

	// title
	printf("\nHANGMAN\n");
	printf("Type 'quit' at any moment to exit the program.\n\n");

	// game loop
	while (numCorrect < lengthOfWord)
	{

		printf("Hangman word:\n");

		for(loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
		{
			if(letterGuessed[loopIndex] == 1)
			{
				printf("%c", guessWords[randomIndex][loopIndex]);
			}
			else
			{
				printf("-");
			}
		}

		printf("\n");

		//printf("Number correct so far: %d\n ", numCorrect);
		printf("Guess a letter: "); // prompt user to make a guess
		fgets(guess, 16, stdin); // store user input in guess var (no more than 16 chars)

		// if user wants to quit
		if(strncmp(guess, "quit", 4) == 0)
		{
			quit = 1;
			break;
		}

		letterEntered = guess[0];

		printf("  You entered: %c\n", letterEntered);

		oldCorrect = numCorrect;

		// loop through characters in selected word
		for(loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
		{
			// prevent user from entering the same guess over and over
			if(letterGuessed[loopIndex] == 1)
			{
				continue;
			}

			// set letterGuessed index to 1 if user guesses correctly
			if(letterEntered == guessWords[randomIndex][loopIndex])
			{
				letterGuessed[loopIndex] = 1;
				numCorrect++;
			}
		}

		// user guess is wrong
		if(oldCorrect == numCorrect)
		{
			numLives--;

			printf("\nWrong!\n\n");

			system("pause");
			system("CLS");

			if(numLives == 6)
			{
				printf("H-\n\n");
			}
			else if(numLives == 5)
			{
				printf("H-A-\n\n");
			}
			else if(numLives == 4)
			{
				printf("H-A-N-\n\n");
			}
			else if(numLives == 3)
			{
				printf("H-A-N-G-\n\n");
			}
			else if(numLives == 2)
			{
				printf("H-A-N-G-M-\n\n");
			}
			else if(numLives == 1)
			{
				printf("H-A-N-G-M-A-\n\n");
			}
			else if(numLives == 0)
			{
				break; // ran out of lives
			}
		}
		else // user guess is right
		{
			printf("\nCorrect!\n\n");

			system("pause");
			system("CLS");

			if(numLives == 6)
			{
				printf("H-\n\n");
			}
			else if(numLives == 5)
			{
				printf("H-A-\n\n");
			}
			else if(numLives == 4)
			{
				printf("H-A-N-\n\n");
			}
			else if(numLives == 3)
			{
				printf("H-A-N-G-\n\n");
			}
			else if(numLives == 2)
			{
				printf("H-A-N-G-M-\n\n");
			}
			else if(numLives == 1)
			{
				printf("H-A-N-G-M-A-\n\n");
			}
			else if(numLives == 0)
			{
				break;
			}
		}
	}

	// user choose to quit early
	if(quit == 1)
	{
		printf("\nExiting HANGMAN\n");
	}
	else if(numLives == 0) // user lost
	{
		printf("H-A-N-G-M-A-N\n\n");
		printf("You lose! The word was: %s\n", guessWords[randomIndex]);
	}
	else // user won
	{
		printf("You win! The word was: %s\n", guessWords[randomIndex]);
	}

	return 0;

}



