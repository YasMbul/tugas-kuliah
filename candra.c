#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int value;
} Element;

typedef struct {
    Element data[MAX];
    int size;       
    int start;
} CircularQueue;

int pilihMenu (){
    int pil;
    printf("=============================================================================\n");
    printf("|                               QUEUE PROGRAM                               |\n");
    printf("|---------------------------------------------------------------------------|\n");
    printf("|                                                                           |\n");
    printf("|                           1. Input Queue                                  |\n");
    printf("|                           2. Tampilkan Queue                              |\n");
    printf("|                           3. Cari Elemen                                  |\n");
    printf("|                           4. Edit Elemen                                  |\n");
    printf("|                           5. Hapus Elemen                                 |\n");
    printf("|                           6. Nilai total, rata-rata,                      |\n");
    printf("|                              terbesar dan terkecil                        |\n");
    printf("|                           7. Exit Program                                 |\n");
    printf("|                                                                           |\n");
    printf("|***************************************************************************|\n");
    printf("=============================================================================\n");
    printf("                            Masukkan Pilihan anda : "); 
    scanf("%d", &pil);
    return pil;
}

void initQueue(CircularQueue *q) {
    q->size = 0;
    q->start = 0;
}

int isFull(CircularQueue *q) {
    return q->size == MAX;
}

int isEmpty(CircularQueue *q) {
    return q->size == 0;
}

void enqueue(CircularQueue *q, Element el) {
    if (isFull(q)) {
        printf("Queue penuh!\n");
        return;
    }

    int end = (q->start + q->size) % MAX;
    q->data[end] = el;
    q->size++;
    printf("Elemen berhasil ditambahkan!\n");
}

void displayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    printf("Isi Queue:\n");
    for (int i = 0; i < q->size; i++) {
        int index = (q->start + i) % MAX;
        printf("%d ", q->data[index].value);
    }
    printf("\n");
}

void searchQueue(CircularQueue *q, int value) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    for (int i = 0; i < q->size; i++) {
        int index = (q->start + i) % MAX;
        if (q->data[index].value == value) {
            printf("Ditemukan: %d\n", q->data[index].value);
            return;
        }
    }
    printf("Elemen tidak ditemukan!\n");
}

void editQueue(CircularQueue *q, int oldValue, int newValue) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    for (int i = 0; i < q->size; i++) {
        int index = (q->start + i) % MAX;
        if (q->data[index].value == oldValue) {
            q->data[index].value = newValue;
            printf("Data berhasil diperbarui!\n");
            return;
        }
    }
    printf("Elemen tidak ditemukan!\n");
}

void dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    printf("Elemen %d dihapus!\n", q->data[q->start].value);
    q->start = (q->start + 1) % MAX;
    q->size--;
}

void rerata(CircularQueue *q){
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return;
    }
    
    double total = 0;
    int bigest = q->data[q->start].value;
    int smallest = q->data[q->start].value;

    for (int i = 0; i < q->size; i++) {
        int index = (q->start + i) % MAX;
        int current = q->data[index].value;
        total += current;

        if (current > bigest) {
            bigest = current;
        }
        if (current < smallest) {
            smallest = current;
        }
    }

    double rata = total / q->size;

    printf("Jumlah nilai dalam Queue = %.2lf\n", total);
    printf("Dengan rata-rata = %.2lf\n", rata);
    printf("Nilai terbesar dalam Queue = %d\n", bigest);
    printf("Nilai terkecil dalam Queue = %d\n", smallest);
}

int main() {
    CircularQueue q;
    initQueue(&q);
    int pil, value, newValue;
    Element el;
    char input[10];
    
    while (1) {
        system("cls");  
        pil = pilihMenu();
        
        switch (pil) {
            case 1:
                while (1) {
                    printf("Masukkan bilangan (ketik 'n' untuk berhenti): ");
                    scanf("%s", input);
                    if (input[0] == 'n' || input[0] == 'N') break;
                    el.value = atoi(input);
                    enqueue(&q, el);
                }
                break;
            case 2:
                displayQueue(&q);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar();  // Wait for user to press Enter
                break;
            case 3:
                if (isEmpty(&q)){
                    printf("Queue Kosong!\n");
                    break;
                }
                printf("Masukkan bilangan yang dicari: ");
                scanf("%d", &value);
                searchQueue(&q, value);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar();  // Wait for user to press Enter
                break;
            case 4:
                if (isEmpty(&q)){
                    printf("Queue Kosong!\n");
                    break;
                }
                printf("Masukkan bilangan yang ingin diedit: ");
                scanf("%d", &value);
                printf("Masukkan bilangan baru: ");
                scanf("%d", &newValue);
                editQueue(&q, value, newValue);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar();  // Wait for user to press Enter
                break;
            case 5:
                dequeue(&q);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar();  // Wait for user to press Enter
                break;
            case 6:
                rerata(&q);
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar();  // Wait for user to press Enter
                break;
            case 7:
                printf("Keluar dari program.\n");
                printf("Terima kasih telah menggunakan program!\n");
                return 0;  // Langsung keluar dari program
            default:
                printf("Pilihan tidak valid!\n");
                printf("\nTekan Enter untuk melanjutkan...");
                getchar(); getchar();  // Wait for user to press Enter
        }
    }
    
    return 0;
}