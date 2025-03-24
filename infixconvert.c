#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Struktur Stack
typedef struct {
    char items[MAX];
    int top;
} Stack;

// Inisialisasi stack
void initStack(Stack *s) {
    s->top = -1;
}

// Cek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Cek apakah stack penuh
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Push elemen ke stack
void push(Stack *s, char value) {
    if (!isFull(s)) {
        s->items[++(s->top)] = value;
    }
}

// Pop elemen dari stack
char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

// Mengambil elemen puncak stack tanpa menghapusnya
char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return -1;
}

// Prioritas operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Konversi dari infix ke postfix
void toPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i, j = 0;
    
    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];
        
        // Jika operand, langsung tambahkan ke output
        if (isalnum(token)) {
            postfix[j++] = token;
        }
        // Jika '(', push ke stack
        else if (token == '(') {
            push(&s, token);
        }
        // Jika ')', pop hingga menemukan '('
        else if (token == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // Hapus '(' dari stack
        }
        // Jika operator
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token)) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }
    
    // Pop semua sisa operator di stack
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    
    postfix[j] = '\0'; // Akhiri string postfix
}

int main() {
    system("cls");
    char infix[MAX], postfix[MAX];
    
    printf("Masukkan infix: ");
    scanf("%s", infix);
    
    toPostfix(infix, postfix);
    
    printf("Hasil postfix: %s\n", postfix);
    
    return 0;
}