#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Struktur Stack
typedef struct {
    char items[MAX][MAX]; // Stack menyimpan string untuk menangani angka lebih dari satu digit
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
void push(Stack *s, char *value) {
    if (!isFull(s)) {
        strcpy(s->items[++(s->top)], value);
    }
}

// Pop elemen dari stack
char* pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return "";
}

// Mengambil elemen puncak stack tanpa menghapusnya
char* peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return "";
}

// Prioritas operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Konversi dari infix ke postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    char number[MAX];
    int numIndex = 0;
    
    while (infix[i] != '\0') {
        char token = infix[i];
        
        // Jika digit, simpan dalam buffer number
        if (isdigit(token)) {
            number[numIndex++] = token;
        } else {
            // Jika ada angka yang terkumpul, tambahkan ke postfix
            if (numIndex > 0) {
                number[numIndex] = '\0';
                strcat(postfix, number);
                strcat(postfix, " "); // Spasi sebagai pemisah
                numIndex = 0;
            }
            
            // Jika '(', push ke stack
            if (token == '(') {
                char temp[2] = {token, '\0'};
                push(&s, temp);
            }
            // Jika ')', pop hingga menemukan '('
            else if (token == ')') {
                while (!isEmpty(&s) && peek(&s)[0] != '(') {
                    strcat(postfix, pop(&s));
                    strcat(postfix, " ");
                }
                pop(&s); // Hapus '(' dari stack
            }
            // Jika operator
            else {
                while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(token)) {
                    strcat(postfix, pop(&s));
                    strcat(postfix, " ");
                }
                char temp[2] = {token, '\0'};
                push(&s, temp);
            }
        }
        i++;
    }
    
    // Jika ada angka terakhir dalam buffer, tambahkan ke postfix
    if (numIndex > 0) {
        number[numIndex] = '\0';
        strcat(postfix, number);
        strcat(postfix, " ");
    }
    
    // Pop semua sisa operator di stack
    while (!isEmpty(&s)) {
        strcat(postfix, pop(&s));
        strcat(postfix, " ");
    }
    
    postfix[strlen(postfix) - 1] = '\0'; // Hapus spasi terakhir
}

int main() {
    system("cls");
    char infix[MAX], postfix[MAX] = "";
    
    printf("Masukkan infix: ");
    fgets(infix, MAX, stdin);
    
    infixToPostfix(infix, postfix);
    
    printf("Hasil postfix: %s\n", postfix);
    
    return 0;
}
