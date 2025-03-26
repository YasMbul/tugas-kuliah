#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Struktur Stack untuk Operator
typedef struct {
    int top;
    char items[MAX];
} Stack;

// Struktur Stack untuk Evaluasi Angka
typedef struct {
    int top;
    int items[MAX];
} IntStack;

// ==== FUNGSI STACK UNTUK OPERATOR ====
void push(Stack *s, char item) {
    s->items[++(s->top)] = item;
}

char pop(Stack *s) {
    if (s->top == -1) return -1;
    return s->items[(s->top)--];
}

char peek(Stack *s) {
    return s->items[s->top];
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// ==== KONVERSI INFIKS KE POSTFIKS ====
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    s.top = -1;
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (s.top != -1 && peek(&s) != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            pop(&s);
        } else {
            while (s.top != -1 && precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, infix[i]);
        }
    }
    while (s.top != -1) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    postfix[j - 1] = '\0';
}

// ==== FUNGSI STACK UNTUK EVALUASI ====
void pushInt(IntStack *s, int item) {
    s->items[++(s->top)] = item;
}

int popInt(IntStack *s) {
    return s->items[(s->top)--];
}

// ==== EVALUASI EKSPRESI POSTFIKS ====
int evaluatePostfix(char *postfix) {
    IntStack s;
    s.top = -1;
    int i = 0;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushInt(&s, num);
        } else if (postfix[i] != ' ') {
            int val2 = popInt(&s);
            int val1 = popInt(&s);
            switch (postfix[i]) {
                case '+': pushInt(&s, val1 + val2); break;
                case '-': pushInt(&s, val1 - val2); break;
                case '*': pushInt(&s, val1 * val2); break;
                case '/': pushInt(&s, val1 / val2); break;
            }
        }
        i++;
    }
    return popInt(&s);
}

// ==== FUNGSI UTAMA ====
int main() {
    char infix[MAX], postfix[MAX];
    printf("Masukkan ekspresi infiks: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Ekspresi dalam notasi postfiks: %s\n", postfix);
    printf("Hasil evaluasi: %d\n", evaluatePostfix(postfix));
    return 0;
}