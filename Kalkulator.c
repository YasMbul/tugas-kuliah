#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20


struct stack {
    char infix[MAX], postfix[MAX], save[MAX];
};


void main(){
    system("cls");
    struct stack convert;
    
    printf("Masukkan infix : "); scanf("%s", &convert.infix);

    int panj = strlen(convert.infix);

    for (int i = 0; i < strlen(convert.infix); i++){
        printf("%c ", convert.infix[i]);
    }


    
}

