#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

typedef struct {
    int nilai;
} Elemen;

typedef struct {
    Elemen data[MAX];
    int head, tail;
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
    printf("                         Masukkan Pilihan anda : "); 
    scanf("%d", &pil);
    system("cls");
    return pil;
}

void emptyQueue(Queue *q) {
    q->head = q->tail = -1;
}

int isFull(Queue *q) {
    return q->tail == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->head == -1 || q->head > q->tail;
}

int enqueue(Queue *q, Elemen el) {
    if (isFull(q)) {
        printf("Queue penuh!\n");
        return 0;
    }
    if (isEmpty(q)) q->head = 0;
    q->data[++q->tail] = el;
    printf("Elemen berhasil ditambahkan!\n");
    return 1;
}

void tampilQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    printf("Isi Queue:\n");
    for (int i = q->head; i <= q->tail; i++) {
        printf("%d ", q->data[i].nilai);
    }
    printf("\nPanjang Queue / Banyak elemen : %d\n", q->tail + 1);
}

int searchQueue(Queue *q, int value) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return 0;
    }
    for (int i = q->head; i <= q->tail; i++) {
        if (q->data[i].nilai == value) {
            printf("Ditemukan: %d\n", q->data[i].nilai);
            printf("Elemen ke-%d dari %d elemen\n", i+1, q->tail + 1);
            return 1;
        }
    }
    printf("Elemen tidak ditemukan!\n");
    return 0;
}

void editQueue(Queue *q, int lama, int baru) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    for (int i = q->head; i <= q->tail; i++) {
        if (q->data[i].nilai == lama) {
            q->data[i].nilai = baru;
            printf("Data urutan ke-%d berhasil diperbarui!\n", i+1);
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
    printf("Elemen %d dihapus!\n", q->data[q->head].nilai);
    for (int i = 0; i < q->tail; i++){
        q->data[i].nilai = q->data[i+1].nilai;
    }
    q->tail--;
    if (q->head > q->tail) emptyQueue(q);
}

void cekData(Queue *q){
    double total = 0;
    double rata = 0;
    int bigest = 0, smallest = q->data[q->head].nilai;
    for (int i = 0; i <= q->tail; i++){
        total += q->data[i].nilai;
    }
    rata = total / (q->tail + 1);

    for (int i = 0; i <= q->tail; i++){
        if (q->data[i].nilai > bigest){
            bigest = q->data[i].nilai;
        }
        if (q->data[i].nilai < smallest){
            smallest = q->data[i].nilai;
        }
    }

    printf("Jumlah nilai dalam Queue = %.2lf\n", total);
    printf("Dengan rata-rata = %.2lf\n", rata);
    printf("Nilai terbesar dalam Queue = %d\n", bigest);
    printf("Nilai terkecil dalam Queue = %d\n", smallest);
}
void enter(){
    printf("\nEnter untuk melanjutkan");
    getchar();
    getchar();
    system("cls");
}
void delay(int detik){
    int milidetik = 1000 * detik;

    clock_t mulai = clock();

    while (clock() < mulai + milidetik);
    system("cls");
}

int main() {
    system("cls");
    Queue q;
    emptyQueue(&q);
    int pil, value, update;
    Elemen el;
    char input[10];
    
    do {
        int pil = pilihMenu();
        switch (pil) {
            case 1:
                while (1) {
                    printf("Masukkan bilangan (ketik 'n' untuk berhenti): ");
                    scanf("%s", input);
                    if (input[0] == 'n' || input[0] == 'N') break;
                    el.nilai = atoi(input);
                    if (enqueue(&q, el) == 0) break;
                }
                delay(2);
                break;
            case 2:
                tampilQueue(&q);
                enter();
                break;
            case 3:
                if (isEmpty(&q)){
                    printf("Queue Kosong!\n");
                    delay(2);
                    break;
                }
                printf("Masukkan bilangan yang dicari: ");
                scanf("%d", &value);
                searchQueue(&q, value);
                delay(2);
                break;
            case 4:
                if (isEmpty(&q)){
                    printf("Queue Kosong!\n");
                    delay(2);
                    break;
                }
                tampilQueue(&q);
                printf("Masukkan bilangan yang ingin diedit: ");
                scanf("%d", &value);
                system("cls");
                if (searchQueue(&q, value) == 0) {
                    delay(2);
                    break;
                }
                printf("Masukkan bilangan baru: ");
                scanf("%d", &update);
                editQueue(&q, value, update);
                enter();
                break;
            case 5:
                dequeue(&q);
                enter();
                break;
            case 6:
                if (isEmpty(&q)){
                    printf("Queue kosong!\n");
                    delay(2);
                    break;
                }
                cekData(&q);
                enter();
                break;
            case 7:
                printf("Keluar dari program Queue!\n");
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
                delay(2);
        }
    } while (pil != 7);
    
    return 0;
}