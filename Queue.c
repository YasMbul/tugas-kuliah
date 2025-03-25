#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Struktur data untuk elemen queue
typedef struct {
    int value;
} Element;

// Struktur queue
typedef struct {
    Element data[MAX];
    int front, rear;
} Queue;

int pilihMenu (){
    int pil;
    printf("=============================================================================\n");
    printf("|                               TUGAS QUEUE                                 |\n");
    printf("|---------------------------------------------------------------------------|\n");
    printf("|                                                                           |\n");
    printf("|                           1. Input Queue                                  |\n");
    printf("|                           2. Tampilkan Queue                              |\n");
    printf("|                           3. Cari Elemen                                  |\n");
    printf("|                           4. Edit Elemen                                  |\n");
    printf("|                           5. Hapus Elemen                                 |\n");
    printf("|                           6. Nilai total, rata-rata,                      |\n");
    printf("|                              terbesar dan terkecil                        |\n");
    printf("|                           7. Exit                                         |\n");
    printf("|                                                                           |\n");
    printf("|***************************************************************************|\n");
    printf("=============================================================================\n");
    printf("                            Masukkan Pilihan anda : "); 
    scanf("%d", &pil);
    system("cls");
    return pil;
}

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

void enqueue(Queue *q, Element el) {
    if (isFull(q)) {
        printf("Queue penuh!\n");
        return;
    }
    if (isEmpty(q)) q->front = 0;
    q->data[++q->rear] = el;
    printf("Elemen berhasil ditambahkan!\n");
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    printf("Isi Queue:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i].value);
    }
    printf("\n");
}

void searchQueue(Queue *q, int value) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        if (q->data[i].value == value) {
            printf("Ditemukan: %d\n", q->data[i].value);
            return;
        }
    }
    printf("Elemen tidak ditemukan!\n");
}

void editQueue(Queue *q, int oldValue, int newValue) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        if (q->data[i].value == oldValue) {
            q->data[i].value = newValue;
            printf("Data berhasil diperbarui!\n");
            return;
        }
    }
    printf("Elemen tidak ditemukan!\n");
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    printf("Elemen %d dihapus!\n", q->data[q->front].value);
    q->front++;
    if (q->front > q->rear) initQueue(q);
}

int main() {
    system("cls");
    Queue q;
    initQueue(&q);
    char cek;
    int pil, value, newValue;
    Element el;
    
    do {
        int pil = pilihMenu();
        switch (pil) {
            case 1:
                do{
                    printf("Masukkan bilangan: ");
                    scanf("%d", &el.value);
                    enqueue(&q, el);
                    printf("Apakah anda ingin menginput bilangan lagi? (Y/y) "); 
                    scanf("%c", &cek);
                    getchar();
                    system("cls");
                } while (cek == 'Y' || cek == 'y');
                break;
            case 2:
                displayQueue(&q);
                break;
            case 3:
                printf("Masukkan bilangan yang dicari: ");
                scanf("%d", &value);
                searchQueue(&q, value);
                break;
            case 4:
                printf("Masukkan bilangan yang ingin diedit: ");
                scanf("%d", &value);
                printf("Masukkan bilangan baru: ");
                scanf("%d", &newValue);
                editQueue(&q, value, newValue);
                break;
            case 5:
                dequeue(&q);
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pil != 6);
    
    return 0;
}


