#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct mobil {
   int nmr;
   struct mobil* next;
} mobil;

mobil* head = NULL;
mobil* tail = NULL;
mobil* top = NULL;

bool isEmptyQueue() {
   return head == NULL;
}

bool isEmptyStack() {
   return top == NULL;
}

void push(mobil* node) {
   node->next = top;
   top = node;
}

mobil* pop() {
   if (isEmptyStack())
      return NULL;
   mobil* temp = top;
   top = top->next;
   temp->next = NULL;
   return temp;
}

void enqueue(int jumlah) {
   for (int i = 1; i <= jumlah; i++) {
      mobil* baru = (mobil*)malloc(sizeof(mobil));
      baru->nmr = (tail ? tail->nmr + 1 : 1);
      baru->next = NULL;

      if (isEmptyQueue()) {
            head = tail = baru;
      } else {
            tail->next = baru;
            tail = baru;
      }
   }
}

void dequeue(int nomorMobil) {
   if (isEmptyQueue()) {
      printf("Parkiran masih kosong! Masukkan mobil terlebih dahulu!\n");
      return;
   }
   mobil* temp = head;
   mobil* prev = NULL;
   bool found = false;

    // Pindahkan mobil ke stack sampai ketemu
   while (temp != NULL) {
      if (temp->nmr == nomorMobil) {
            found = true;
            if (temp == head) {
               head = head->next;
            } else {
               prev->next = temp->next;
               if (temp == tail) {
                  tail = prev;
               }
            }
            free(temp);
            break;
      } else {
            mobil* next = temp->next;

            // Putus dari queue, simpan di stack
            if (temp == head) {
               head = head->next;
            } else {
               prev->next = next;
               if (temp == tail) {
                  tail = prev;
               }
            }

            temp->next = NULL;
            push(temp);
            temp = next;
      }
      prev = temp;
   }

   if (!found) {
      printf("Mobil dengan nomor %d tidak ditemukan di parkiran.\n", nomorMobil);
   }

      // Kalau sudah kosong (tidak ada mobil dikembalikan), set tail ke NULL juga
      if (isEmptyStack() && head == NULL) {
         tail = NULL;
      }

     // Kembalikan mobil dari stack ke queue
      while (!isEmptyStack()) {
         mobil* kembalian = pop();
         kembalian->next = head;
         head = kembalian;
      }

     // Update tail setelah semua dikembalikan
      if (head != NULL) {
         mobil* tempTail = head;
         while (tempTail->next != NULL) {
            tempTail = tempTail->next;
         }
         tail = tempTail;
      }
}

void tampilkan() {
   if (isEmptyQueue()) {
      printf("Parkiran kosong.\n");
      return;
   }

   mobil* temp = head;
   printf("Isi parkiran: \n");
   while (temp != NULL) {
      printf("%d < ", temp->nmr);
      temp = temp->next;
   }
   printf("Utara\n");
}

void enter() {
   printf("\nEnter untuk melanjutkan");
   getchar();
   getchar();
   system("cls");
}

int main() {
   int jum, pil;
   system("cls");
   do {
      system("cls");
      printf("\nMenu:\n");
      printf("1. Masukkan mobil\n");
      printf("2. Keluarkan mobil\n");
      printf("3. Tampilkan parkiran\n");
      printf("4. Keluar program\n");
      printf("Pilih: ");
      scanf("%d", &pil);

      switch (pil) {
         case 1:
            printf("Masukkan banyak mobil : ");
            scanf("%d", &jum);
            enqueue(jum);
            sleep(2);
            break;
         case 2:
            printf("Nomor mobil yang ingin dikeluarkan : ");
            scanf("%d", &jum);
            dequeue(jum);
            sleep(2);
            break;
         case 3:
            tampilkan();
            enter();
            break;
         case 4:
            printf("Program selesai!\n");
            break;
         default:
            printf("Pilihan tidak valid.\n");
            sleep(1);
         }
   } while (pil != 4);

   return 0;
}
