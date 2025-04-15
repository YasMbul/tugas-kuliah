#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node {
   int data;
   struct Node* next;
} Node;

Node* head = NULL;

// Cek apakah linked list kosong
bool isEmpty() {
   if (head == NULL) {
      return true;
   } else {
      return false;
   }
}

// Tambah elemen ke akhir linked list
void tambahBelakang(int value) {
   Node* baru = (Node*)malloc(sizeof(Node));
   baru->data = value;
   baru->next = NULL;

   if (isEmpty()) {
      head = baru;
   } else {
      Node* temp = head;
      while (temp->next != NULL) {
            temp = temp->next;
      }
      temp->next = baru;
   }
   printf("Data %d berhasil ditambahkan.\n", value);
}

void tambahDepan(int value) {
   Node* baru = (Node*)malloc(sizeof(Node));
   baru->data = value;
   baru->next = NULL;

   if(isEmpty()){
      head = baru;
   } else {
      baru->next = head;
      head = baru;
   }
   printf("Data %d berhasil ditambahkan.\n", value);
}

// Hapus elemen pertama
void hapusDepan() {
   if (isEmpty()) {
      printf("Linked list kosong, tidak ada yang bisa dihapus.\n");
      return;
   }
   Node* temp = head;
   head = head->next;
   printf("Data %d berhasil dihapus.\n", temp->data);
   free(temp);
}

void hapusBelakang() {
   if (isEmpty()) {
      printf("Linked list kosong, tidak ada yang bisa dihapus.\n");
      return;
   }

   if (head->next == NULL) {
      printf("Data %d berhasil dihapus.\n", head->data);
      free(head);
      head = NULL;
      return;
   }

   Node* temp = head;
   Node* prev = NULL;

   while (temp->next != NULL) {
      prev = temp;
      temp = temp->next;
   }

   printf("Data %d berhasil dihapus.\n", temp->data);
   free(temp);
   prev->next = NULL;
}

// Tampilkan semua elemen
void tampilkan() {
   if (isEmpty()) {
      printf("Linked list kosong.\n");
      return;
   }
   Node* temp = head;
   printf("Isi linked list: ");
   while (temp != NULL) {
      printf("%d > ", temp->data);
      temp = temp->next;
   }
   printf("NULL\n");
}


void enter() {
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

// Menu utama
int main() {
   int pilihan, data, subpil;
   system("cls");
   
   do {
      system("cls");
      printf("\nMenu:\n");
      printf("1. Tambah data\n");
      printf("2. Hapus data\n");
      printf("3. Tampilkan data\n");
      printf("4. Cek apakah kosong\n");
      printf("5. Keluar\n");
      printf("Pilih: ");
      scanf("%d", &pilihan);

      switch (pilihan) {
         case 1:
            system("cls");
            printf("1. tambah dari depan\n");
            printf("2. tambah dari belakang\n");
            printf("Pilih: ");
            scanf("%d", &subpil);
            printf("Masukkan data: ");
            scanf("%d", &data);
            switch (subpil) {
               case 1:
                  tambahDepan(data);
                  delay(2);
                  break;
               case 2: 
                  tambahBelakang(data);
                  delay(2);
                  break;
            }
            break;
         case 2:
            system("cls");
            printf("1. Hapus dari depan\n");
            printf("2. Hapus dari belakang\n");
            printf("Pilih: ");
            scanf("%d", &subpil);
            switch(subpil) {
               case 1:
                  hapusDepan(); // hapus dari depan
                  delay(2);
                  break;
               case 2:
                  hapusBelakang(); // hapus dari belakang
                  delay(2);
                  break;
               default:
                  printf("Pilihan tidak valid.\n");
            }
            break;
         case 3:
            tampilkan();
            enter();
            break;
         case 4:
            if(isEmpty())
               printf("Linked list kosong.\n");
            else 
               printf("Linked list tidak kosong.\n");
            enter();
            break;
         case 5:
            printf("Program selesai.\n");
            break;
         default:
            printf("Pilihan tidak valid.\n");
      }
   } while (pilihan != 5);

   return 0;
}
