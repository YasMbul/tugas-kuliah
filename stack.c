#include <conio.h>
#include <stdio.h>
#include <malloc.h>

typedef struct node *list;

struct node {
   int data;
   struct node *next; 
}node; 
struct node *head;

void init() {
   head=NULL;
}

int isEmpty() {
   if(head==NULL) 
      return 1;
   else 
      return 0;
}

void push (int databaru, list new) {
   new = (list) malloc (sizeof(node));

   if (new==NULL)
      exit;
   new->data = databaru;
   new->next = NULL;
   if (isEmpty()==1) {
      head = new;
      head->next = NULL;
   }
   else {
      new->next = head;
      head = new;
   }
   return 1;
}

void pop() {
   struct node *hapus;
   int d; 
   if (isEmpty() == 0) {
      if (head->next != NULL) {
         hapus = head;
         d = hapus->data;
         head = head->next;
         free(hapus) ;
      }
      else {
         d = head->data;
         head = NULL;
      }
   }
}

void tampil() {
   struct node *bantu;
   bantu = head;
   if (isEmpty() == 0){
      while (bantu != NULL){
         printf("%3d", bantu->data);
         bantu = bantu->next;
      }
      printf("\n");
   }
   else 
      printf("Masih kosong\n");
}

void main() {
   int data;
   int databaru;
   printf(" PROGRAM STACK  \n");
   printf("Isi Stack awal  \n");
   tampil();
   printf("\n");
   printf("Memasukkan data menggunakan PUSH \n");
   push(12, 1);
   push(30, 2);
   push(15, 3);
   tampil();
   printf("\n");
   printf("Menghapus data menggunakan POP \n");
   pop();
   tampil();
   getch();
}