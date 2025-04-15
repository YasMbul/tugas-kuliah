#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef struct mobil {
   int nmr;
   struct mobil* next;
} mobil;

mobil* qhead = NULL;
mobil* qtail = NULL;
mobil* shead = NULL;

bool isEmpty(char tipe) {
   if(tipe == "q"){
      if(qhead == NULL)
         return true;
      else 
         return false;
   }
   if(tipe == "s"){
      if(shead == NULL)
         return true;
      else 
         return false;
   }
}

void enqueue(int nmr) {
   if(isEmpty(q)) {
      for(int i = 1; i <= nmr; i++){
         mobil* baru = (mobil*)malloc(sizeof(mobil));
         baru->nmr = i;
         baru->next = NULL;
         if(isEmpty(q))
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

