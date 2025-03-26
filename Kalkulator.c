#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    char items[MAX][MAX]; 
    int top;
} Stack;

typedef struct {
    double items[MAX];
    int top;
} DStack;

void emptyStack(Stack *s) {
    s->top = -1;
}

void emptyDStack(DStack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isDStackEmpty(DStack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

int isDStackFull(DStack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char *value) {
    if (!isFull(s)) {
        strcpy(s->items[++(s->top)], value);
    }
}

void pushD(DStack *s, double value) {
    if (!isDStackFull(s)) {
        s->items[++(s->top)] = value;
    }
}

char* pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return "";
}

double popD(DStack *s) {
    if (!isDStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return 0;
}

char* akses(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return "";  
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    emptyStack(&s);
    int i = 0, j = 0;
    char number[MAX];
    int numIndex = 0;
    
    while (infix[i] != '\0') {
        char token = infix[i];

        if (isdigit(token)) {
            number[numIndex++] = token;
        } else {
            if (numIndex > 0) {
                number[numIndex] = '\0';
                strcat(postfix, number);
                strcat(postfix, " "); 
                numIndex = 0;
            }
            
            if (token == '(') {
                char temp[2] = {token, '\0'};
                push(&s, temp);
            }

            else if (token == ')') {
                while (!isEmpty(&s) && akses(&s)[0] != '(') {
                    strcat(postfix, pop(&s));
                    strcat(postfix, " ");
                }
                pop(&s); 
            }

            else {
                while (!isEmpty(&s) && precedence(akses(&s)[0]) >= precedence(token)) {
                    strcat(postfix, pop(&s));
                    strcat(postfix, " ");
                }
                char temp[2] = {token, '\0'};
                push(&s, temp);
            }
        }
        i++;
    }
    
    if (numIndex > 0) {
        number[numIndex] = '\0';
        strcat(postfix, number);
        strcat(postfix, " ");
    }
    
    while (!isEmpty(&s)) {
        strcat(postfix, pop(&s));
        strcat(postfix, " ");
    }
    
    postfix[strlen(postfix) - 1] = '\0'; 
}

double hasilPostfix(char *postfix) {
    DStack s;
    emptyDStack(&s);
    char *token = strtok(postfix, " ");
    
    while (token != NULL) {
        if (isdigit(token[0])) {
            pushD(&s, atof(token));
        } else {
            double val2 = popD(&s);
            double val1 = popD(&s);
            double result;
            
            switch (token[0]) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': result = val1 / val2; break;
                case '^': result = pow(val1, val2); break;
                default: result = 0; break;
            }
            
            pushD(&s, result);
        }
        token = strtok(NULL, " ");
    }
    
    return popD(&s);
}

int main() {
    system("cls");
    char infix[MAX];
    char jwb;
    do {
        char postfix[MAX] = "";
        printf("Masukkan peritungan : ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = 0; 
        
        infixToPostfix(infix, postfix);
        printf("Ekspresi postfix: %s\n", postfix);
        
        double hasil = hasilPostfix(postfix);
        printf("Hasil perhitungan: %.2lf\n", hasil);

        printf("Apakah ingin mengulang maka ketik (Y/y) "); scanf("%c", &jwb);
        getchar();
    } while (jwb == 'y' || jwb == 'Y');
    printf("Program selesai!");
    return 0;
}
