#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Struktur Stack untuk konversi infix ke postfix
typedef struct {
    char items[MAX][MAX]; // Stack menyimpan string untuk menangani angka lebih dari satu digit
    int top;
} Stack;

// Struktur Stack untuk evaluasi postfix
typedef struct {
    double items[MAX];
    int top;
} DoubleStack;

// Inisialisasi stack karakter
void initStack(Stack *s) {
    s->top = -1;
}

// Inisialisasi stack double
void initDoubleStack(DoubleStack *s) {
    s->top = -1;
}

// Cek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

int isDoubleStackEmpty(DoubleStack *s) {
    return s->top == -1;
}

// Cek apakah stack penuh
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

int isDoubleStackFull(DoubleStack *s) {
    return s->top == MAX - 1;
}

// Push elemen ke stack karakter
void push(Stack *s, char *value) {
    if (!isFull(s)) {
        strcpy(s->items[++(s->top)], value);
    }
}

// Push elemen ke stack double
void pushDouble(DoubleStack *s, double value) {
    if (!isDoubleStackFull(s)) {
        s->items[++(s->top)] = value;
    }
}

// Pop elemen dari stack karakter
char* pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return "";
}

// Pop elemen dari stack double
double popDouble(DoubleStack *s) {
    if (!isDoubleStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return 0;
}

// Mengambil elemen paling atas dari stack tanpa menghapusnya
char* peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return ""; // Kembalikan string kosong jika stack kosong
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

// Evaluasi ekspresi postfix
double hasilPostfix(char *postfix) {
    DoubleStack s;
    initDoubleStack(&s);
    char *token = strtok(postfix, " ");
    
    while (token != NULL) {
        // Jika token adalah angka, push ke stack
        if (isdigit(token[0])) {
            pushDouble(&s, atof(token));
        } else {
            // Pop dua angka dari stack
            double val2 = popDouble(&s);
            double val1 = popDouble(&s);
            double result;
            
            // Lakukan operasi yang sesuai
            switch (token[0]) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': result = val1 / val2; break;
                case '^': result = pow(val1, val2); break;
                default: result = 0; break;
            }
            
            // Push hasil ke stack
            pushDouble(&s, result);
        }
        token = strtok(NULL, " ");
    }
    
    return popDouble(&s);
}

int main() {
    system("cls");
    char infix[MAX], postfix[MAX] = "";
    
    printf("Masukkan ekspresi infix: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = 0; // Hapus newline
    
    infixToPostfix(infix, postfix);
    printf("Ekspresi postfix: %s\n", postfix);
    
    double hasil = hasilPostfix(postfix);
    printf("Hasil perhitungan: %.2lf\n", hasil);
    
    return 0;
}
