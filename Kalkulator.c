#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20


typedef struct stack {
    // char infix[MAX], postfix[MAX], save[MAX];
    char *infix, *postfix, *save;
    int top, isi[MAX];
};

void inputInfix();
void push();
void pop();
void insert();
void isFull();
void isEmty();


void debug(struct stack convert){
    // int panj = strlen(convert->infix);
    // printf("%d\n", panj);
    for (int i = 0; i < strlen(convert.infix); i++){
        printf("%c", convert.infix[i]);
    }
}

void main(){
    system("cls");
    struct stack convert;
    
    inputInfix(&convert);
    
    // int panj = strlen(convert.infix);

    // printf("%d\n", panj);

    // for (int i = 0; i < strlen(convert.infix); i++){
    //     printf("%c", convert.infix[i]);
    // }


    // debug(convert);
    
    
    
}

void inputInfix(struct stack *convert){
    printf("Masukkan infix : "); scanf("%s", convert->infix);
    
}