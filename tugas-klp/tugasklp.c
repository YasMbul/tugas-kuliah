#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef struct mobil {
   int nmr;
   struct mobil* next;
} mobil;

mobil* head = NULL;
mobil* tail = NULL;
mobil* top = NULL;

bool isEmptyQueue() {
   if(head == NULL)
      return true;
   else 
      return false;

}

bool isEmptyStack() {
   if(top == NULL)
      return true;
   else 
      return false;
}

void push() {
   if(isEmptyStack()){
      top = head;
      head = head->next;
      top->next = NULL;
   } else {
      mobil* temp = top;
      top = head;
      top->next = temp;
      head = head->next;
   }
}

void pop(mobil* temp) {
   if(isEmptyStack())
      return;
   else {
      top = top->next;
      temp->next = head;
      head = temp;
   }
}

void enqueue(int nmr) {
   if(isEmptyQueue()) {
      for(int i = 1; i <= nmr; i++){
         mobil* baru = (mobil*)malloc(sizeof(mobil));
         baru->nmr = i;
         baru->next = NULL;
         if(isEmptyQueue())
            head = tail = baru;
         else if (head == tail) {
            head->next = baru;
            tail = baru;
         }
         else {
            tail->next = baru;
            tail = baru;
         }
      }
   }
   else {
      for(int i = tail->nmr + 1; i <= tail->nmr + nmr; i++){
         mobil* baru = (mobil*)malloc(sizeof(mobil));
         baru->nmr = i;
         baru->next = NULL;
         if (head == tail) {
            head->next = baru;
            tail = baru;
         }
         else {
            tail->next = baru;
            tail = baru;
         }
      }
   }
}

void dequeue(int mobil) {
   if(isEmptyQueue()) 
      printf("Parkiran masih kosong! Masukkan mobil terlebih dahulu!");
   else {
      mobil* temp2 = head;
      while(temp2->nmr != mobil) {
         push();
         temp2 = temp2->next;
      }
      free(temp);
      temp = top;
      while(top->next != NULL){
         pop(temp);
         temp = temp->next;
      }
   }
}

void tampilkan() {
   if (isEmptyQueue()) {
      printf("Parkiran kosong.\n");
      return;
   }
   mobil* temp = head;
   printf("Isi parkiran: ");
   while (temp != NULL) {
      printf("%d < ", temp->nmr);
      temp = temp->next;
   }
   printf("NULL\n");
}

void main() {
   int jum, pil;
   do {
      printf("\nMenu:\n");
      printf("1. Masukkan mobil\n");
      printf("2. Keluarkan mobil\n");
      printf("3. Tampilkan parkiran\n");
      printf("4. Keluar program\n");
      printf("Pilih: ");
      scanf("%d", &pil);
      switch(pil) {
         case 1:
            printf("Masukkan banyak mobil : "); scanf("%d", &jum);
            enqueue(jum);
            break;
         case 2:
            printf("Nomor mobil yang ingin dikeluarkan : "); scanf("%d", &jum);
            dequeue(jum);
            break;
         case 3: 
            tampilkan();
            break;
         case 4: 
            printf("Program selesai!");
            break;
         default:
            printf("Pilihan tidak valid.\n");
      }
   } while (pil != 4);

}