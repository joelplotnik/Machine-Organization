/* Joel Plotnik - 006642110
 * main.c
 * This program reads a message from a text file, encodes the
 * message using huffman binary encoding, and then transmits the message
 * to a recipient.
 *
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PORT 8080
#define SA struct sockaddr

typedef struct{                 // typedef structure
    char letter;
    int code[12];
    int size;
} huffcode;                     // struct used to store huffman code

extern int read_huffman(FILE * fptr, huffcode hcode[]);
extern int read_message(FILE * fptr, char message[]);
extern int encode(char message[], huffcode hcode[]);

int main (int argc, char *argv[]){
    FILE *fptr;                 // file pointer
    huffcode hcode[29];         // array used to store huffman code
    char message[10000];        // array used to store message from file to encode and send over to recipient
    int messageLngth = 0;

    ///////////////// CLIENT INFORMATION ////////////////
    int socketFp = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address, serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // dif

    if(connect(socketFp, (SA *)&serverAddress, sizeof(serverAddress)) != 0){
            printf("connection failed..\n");
            exit(0);
    }
    ////////////////////////////////////////////////////

    // if no file name arguments in main then open deck.dat to read the huffman code
    if (argc == 1){
        fptr = fopen("huffman.dat", "r");
    }
    else{       // else open the string file name given as an argument to main
        fptr = fopen(argv[1], "r");
    }

    // read the huffman code from the file and store huffman code into hcode array of structs
    read_huffman(fptr, hcode);
    fclose(fptr);               //close "huffman.dat"

    // open the message to encode and send to recipient
    fptr = fopen("message.txt", "r");
    // read the message and store the message into the char array message[10000]
    messageLngth = read_message(fptr, message);
    fclose(fptr);               // close message.txt

    // encode the message stored in the message[] array and send the message as an integer in 32 bit or less chunks
    encode(message, hcode);

    close(socketFp);

    return 0;
}
