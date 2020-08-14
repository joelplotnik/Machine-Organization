A program that simulates the card game “Go Fish”.  Main driver function in C. The main driver calls the individual functions to shuffle the deck of cards, 
deal the cards, ask for a card, and lay down the cards. For this implementation, the variation used is where players give just one card when asked, and lay down pairs.  
Basically the players take turns asking the other player for a card of a certain rank, which the other player must hand over if they have such a card.  
The players goal is to collect matching pairs of cards (of the same rank), placing them on the table.  Score is kept of how many pairs each player has because 
the number of cards each player may hold at any moment in time can be anything (less than 47 of course). 
1. Allocate 47 element array for each player and keep track of the cards in hand; 
2. Use the stack to store the players’ hand; or 
3. Dynamically resize the players’ hands each time the number of cards changes.
The program simulates the playing of the game, with two players (player 1 is the user, player 2 is the computer). 

Rules: Player1 and CPU both start with 5 cards. If Player1 or CPU start with a 
pair it is automatically placed on the table for the first turn. First one to 
13 pairs wins. Plays are recorded in gofish_plays.txt. If Player1 or CPU run out 
of cards, their deck is immediately replenished with 5 cards. 
