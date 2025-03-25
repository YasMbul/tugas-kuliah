#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20

typedef struct {
    int isi[MAX];
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
    printf("|                           4. Cari Elemen                                  |\n");
    printf("|                           5. Edit Elemen                                  |\n");
    printf("|                           6. Hapus Elemen                                 |\n");
    printf("|                           7. Nilai total, rata-rata,                      |\n");
    printf("|                              terbesar dan terkecil                        |\n");
    printf("|                           8. Exit                                         |\n");
    printf("|                                                                           |\n");
    printf("|***************************************************************************|\n");
    printf("=============================================================================\n");
    printf("                            Masukkan Pilihan anda : "); 
    scanf("%d", &pil);
    system("cls");
    return pil;
}

void inisiasi(Queue *q){
    q->head = q->tail = -1;
}
int isFull(Queue *q){
    return q->tail == MAX-1;
}
int isEmpty(Queue *q){
    return q->tail == -1 && q->head == -1;
}
void input(){
    char isi[MAX];
    printf("Input bilangan : "); fgets(isi, MAX, stdin);
    
} 

void main(){
    system("cls");
    Queue q;

    inisiasi(&q);
    int pil = pilihMenu();
    switch(pil){
        case 1 : 
            
        break;
        default : printf("Pilihan tidak ada!");
    }
    
}
