Given the C program below with the given main and checkPrimeNumber functions. The code is rewritten: 
1. The function checkPrimeNumber is rewritten in assembler and called from the main written in C; 
2. The main function is written in assembler and is used to call the function checkPrimeNumber written in C; 
3. Both the main and checkPrimeNumber functions are rewritten in assembler.

#include <stdio.h> 
int checkPrimeNumber(int n); 
int main() 
{ 
    int n1, n2, i, flag; 
 
    printf("Enter two positive integers: "); 
    scanf("%d %d", &n1, &n2); 
    printf("Prime numbers between %d and %d are: ", n1, n2); 
 
    for(i=n1+1; i<n2; ++i) 
    { 
        // i is a prime number, flag will be equal to 1 
        flag = checkPrimeNumber(i); 
 
        if(flag == 1) 
            printf("%d ",i); 
    } 
    return 0; 
} 
