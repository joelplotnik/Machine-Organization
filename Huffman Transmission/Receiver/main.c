/* Joel Plotnik - 006642110
 * main.c
 * This program receives an encoded message, decodes the
 * message, and then displays the message while blinking red and green lights
 * as the binary represenation of the message.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define SA struct sockaddr

typedef struct{                 // typedef structure
    char letter;
    int code[12];
    int size;
} huffcode;                     // struct used to store huffman code

extern int sort_hcode(huffcode hcode[]);
extern int decoder(int encoded_int, huffcode hcode[], int * current_char, char d_message[]);

int main(int argc, char *argv[])
{
    FILE *fptr;                 // file pointer
    huffcode hcode[29];         // array used to store huffman code
    char d_message[10000];      // array used to store the decoded message
    int current_char = 0;


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

    // sort hcode
    sort_hcode(hcode);

    ////////////////////// SERVER INFORMATION ///////////////////////////////
        int socketFp = socket(AF_INET, SOCK_STREAM, 0);
        unsigned int code;

        if(socketFp == -1){
                printf("Socket not made..\n");
                exit(0);
        }

        struct sockaddr_in address;

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        if((bind(socketFp, (SA *)&address , sizeof(address))) != 0){
                printf("Binding failed..\n");
                exit(0);
        }

        if((listen(socketFp, 3)) != 0){
            printf("Listen failed..\n");
            exit(0);
        }

        int addrLen = sizeof(address);

        int new_socket = accept(socketFp, (SA *)&address, (socklen_t *)&addrLen);

        if(new_socket < 0){
                    printf("Accept failed..\n");
                    exit(0);
        }
    //////////////////////////////////////////////////////////////////////////

        // read the int packets and decode them
        while (read(new_socket, &code, sizeof(code)))
        {

            decoder(code, hcode, &current_char, d_message);

        }

        close(socketFp);


        //int n = sizeof(d_message);

    // Print the received messsage
    printf("\n\nThis is the decoded message that was, after decoding, stored in the d_message[10000] array:\n\n");
    for (int i = 0; i < 200 ; ++i) {
        printf("%c", d_message[i]);
    }
    printf("\n\n");

    return 0;
}
