#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mobil {
    char plat[20];
    struct Mobil *next;
} Mobil;

typedef struct Stack {
    Mobil *top;
} Stack;

typedef struct Queue {
    Mobil *front;
    Mobil *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void initStack(Stack *s) {
    s->top = NULL;
}

Mobil* createMobil(const char *plat) {
    Mobil *m = (Mobil*)malloc(sizeof(Mobil));
    strcpy(m->plat, plat);
    m->next = NULL;
    return m;
}

void enqueue(Queue *q, const char *plat) {
    Mobil *m = createMobil(plat);
    if (q->rear == NULL) {
        q->front = q->rear = m;
    } else {
        q->rear->next = m;
        q->rear = m;
    }
    printf("Mobil %s masuk parkiran\n", plat);
}

void tampilkanQueue(Queue q) {
    if (q.front == NULL) {
        printf("Parkiran kosong.\n");
        return;
    }

    Mobil *curr = q.front;
    int index = 1;
    printf("Isi parkiran dari Selatan ke Utara:\n");
    while (curr != NULL) {
        printf("%d. %s\n", index++, curr->plat);
        curr = curr->next;
    }
}

void push(Stack *s, Mobil *m) {
    m->next = s->top;
    s->top = m;
}

Mobil* pop(Stack *s) {
    if (s->top == NULL) return NULL;
    Mobil *temp = s->top;
    s->top = s->top->next;
    return temp;
}

void keluarkanMobilByPlat(Queue *q, const char *plat) {
    Stack s;
    initStack(&s);
    Mobil *curr = q->front;
    int found = 0;

    // pindah ke stack sampai ketemu mobilnya
    while (curr != NULL && strcmp(curr->plat, plat) != 0) {
        Mobil *temp = curr;
        curr = curr->next;
        q->front = curr;
        temp->next = NULL;
        push(&s, temp);
    }

    // keluarkan mobil
    if (curr != NULL && strcmp(curr->plat, plat) == 0) {
        found = 1;
        printf("Mobil %s keluar dari parkiran\n", curr->plat);
        Mobil *toDelete = curr;
        q->front = curr->next;
        free(toDelete);
        if (q->front == NULL)
            q->rear = NULL;
    }

    // kembalikan mobil dari stack
    while (s.top != NULL) {
        Mobil *m = pop(&s);
        m->next = q->front;
        q->front = m;
        if (q->rear == NULL)
            q->rear = m;
    }

    if (!found) {
        printf("Mobil dengan plat %s tidak ditemukan\n", plat);
    }
}

void keluarkanMobilByUrutan(Queue *q, int posisi) {
    if (posisi < 1 || q->front == NULL) {
        printf("Urutan tidak valid.\n");
        return;
    }

    Stack s;
    initStack(&s);
    Mobil *curr = q->front;
    int count = 1;
    int found = 0;

    // pindah ke stack sampai urutan ke-n
    while (curr != NULL && count < posisi) {
        Mobil *temp = curr;
        curr = curr->next;
        q->front = curr;
        temp->next = NULL;
        push(&s, temp);
        count++;
    }

    if (count == posisi && curr != NULL) {
        found = 1;
        printf("Mobil %s (urutan ke-%d) keluar dari parkiran\n", curr->plat, posisi);
        Mobil *toDelete = curr;
        q->front = curr->next;
        free(toDelete);
        if (q->front == NULL)
            q->rear = NULL;
    }

    while (s.top != NULL) {
        Mobil *m = pop(&s);
        m->next = q->front;
        q->front = m;
        if (q->rear == NULL)
            q->rear = m;
    }

    if (!found) {
        printf("Tidak ada mobil di urutan ke-%d\n", posisi);
    }
}

void menu() {
    Queue parkiran;
    initQueue(&parkiran);

    int pilihan;
    char plat[20];
    int jumlah, i, metode, urutan;

    do {
        printf("\n--- SIMULASI PARKIR ---\n");
        printf("1. Mobil Masuk (Banyak Sekaligus)\n");
        printf("2. Mobil Keluar\n");
        printf("3. Lihat Parkiran\n");
        printf("4. Keluar Program\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Berapa mobil yang ingin dimasukkan? ");
                scanf("%d", &jumlah);
                for (i = 0; i < jumlah; i++) {
                    printf("Plat mobil ke-%d: ", i + 1);
                    scanf("%s", plat);
                    enqueue(&parkiran, plat);
                }
                break;
            case 2:
                printf("Metode keluarkan:\n");
                printf("1. Berdasarkan Plat\n");
                printf("2. Berdasarkan Urutan Masuk\n");
                printf("Pilih: ");
                scanf("%d", &metode);
                if (metode == 1) {
                    printf("Masukkan plat mobil: ");
                    scanf("%s", plat);
                    keluarkanMobilByPlat(&parkiran, plat);
                } else if (metode == 2) {
                    printf("Masukkan urutan mobil dari depan (Selatan): ");
                    scanf("%d", &urutan);
                    keluarkanMobilByUrutan(&parkiran, urutan);
                } else {
                    printf("Metode tidak valid.\n");
                }
                break;
            case 3:
                tampilkanQueue(parkiran);
                break;
            case 4:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);
}

int main() {
    menu();
    return 0;
}