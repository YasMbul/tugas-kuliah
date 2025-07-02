#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Struktur Arsip
typedef struct {
   int id;
   char nama[50];
   char tanggal[20];
   char kategori[30];
} Arsip;

// Node Linked List
typedef struct Node {
   Arsip data;
   struct Node* next;
} Node;

Node* head = NULL;

// Stack
Arsip stack[MAX];
int top = -1;

void push(Arsip arsip) {
   if (top < MAX - 1)
   stack[++top] = arsip;
}

Arsip pop() {
   if (top >= 0)
   return stack[top--];
   Arsip kosong = {-1, "", "", ""};
   return kosong;
}


// Queue
Arsip queue[MAX];
int front = 0, rear = 0;

void enqueue(Arsip arsip) {
   if ((rear + 1) % MAX != front) {
      queue[rear] = arsip;
      rear = (rear + 1) % MAX;
   }
}

Arsip dequeue() {
   if (front != rear) {
      Arsip arsip = queue[front];
      front = (front + 1) % MAX;
      return arsip;
   }
   Arsip kosong = {-1, "", "", ""};
   return kosong;
}

int isEmptyQueue(){
   return front == rear;
}

void tampilQueue(){
   printf("\n--- Daftar Antrian ---\n");
   if(isEmptyQueue()){
      printf("Antrian Kosong, silahkan tambahkan arsip!\n");
      return;
   }
   
   int i = front;
   while (i != rear) {
      printf("%s", queue[i].nama);
      i = (i + 1) % MAX;
      if (i != rear) printf(" -> ");
   }
   printf("\n");
}

// Tambah arsip ke linked list
void tambahArsip(Arsip arsip) {
   Node* baru = (Node*)malloc(sizeof(Node));
   baru->data = arsip;
   baru->next = NULL;
   
   if (head == NULL) {
      head = baru;
   } else {
      Node* temp = head;
      while (temp->next != NULL) temp = temp->next;
      temp->next = baru;
   }
}

void editArsip() {
   if (head == NULL) {
      printf("\nTidak ada arsip yang tersedia untuk diedit.\n");
      return;
   }
   
   int idEdit;
   printf("\nMasukkan ID arsip yang ingin diedit: ");
   scanf("%d", &idEdit);
   getchar();  // membersihkan newline dari buffer
   
   Node* temp = head;
   while (temp != NULL) {
      if (temp->data.id == idEdit) {
         printf("Arsip ditemukan: %s\n", temp->data.nama);
         printf("Masukkan data baru (biarkan kosong untuk tidak mengubah):\n");
         
         // Nama
         char input[50];
         printf("Nama [%s]: ", temp->data.nama);
         fgets(input, 50, stdin);
         input[strcspn(input, "\n")] = '\0';
         if (strlen(input) > 0) {
            strcpy(temp->data.nama, input);
         }
         
         // Tanggal
         printf("Tanggal [%s]: ", temp->data.tanggal);
         fgets(input, 20, stdin);
         input[strcspn(input, "\n")] = '\0';
         if (strlen(input) > 0) {
            strcpy(temp->data.tanggal, input);
         }
         
         // Kategori
         printf("Kategori [%s]: ", temp->data.kategori);
         fgets(input, 30, stdin);
         input[strcspn(input, "\n")] = '\0';
         if (strlen(input) > 0) {
            strcpy(temp->data.kategori, input);
         }
         
         for (int i = 0; i <= top; i++) {
            if (stack[i].id == idEdit) {
               stack[i] = temp->data;  
               break;
            }
         }
         printf("\nArsip berhasil diperbarui.\n");
         return;
      }
      temp = temp->next;
   }
   
   printf("\nArsip dengan ID %d tidak ditemukan.\n", idEdit);
}

void hapusArsip() {
   if (head == NULL) {
      printf("\nTidak ada arsip yang tersedia untuk dihapus.\n");
      return;
   }
   
   int idHapus;
   printf("\nMasukkan ID arsip yang ingin dihapus: ");
   scanf("%d", &idHapus);
   getchar();
   
   Node *curr = head, *prev = NULL;
   while (curr != NULL) {
      if (curr->data.id == idHapus) {
         if (prev == NULL) head = curr->next;
         else prev->next = curr->next;
         
         printf("Arsip dengan ID %d dan nama %s berhasil dihapus.\n", curr->data.id, curr->data.nama);
         free(curr);
         return;
      }
      prev = curr;
      curr = curr->next;
   }
   
   printf("Arsip dengan ID %d tidak ditemukan.\n", idHapus);
}


// Tampilkan semua arsip
void tampilArsip() {
   Node* temp = head;
   printf("\n--- Daftar Arsip ---\n");
   while (temp != NULL) {
      printf("ID: %d, Nama: %s, Tanggal: %s, Kategori: %s\n",
         temp->data.id, temp->data.nama, temp->data.tanggal, temp->data.kategori);
         temp = temp->next;
      }
   }
   
   // Searching
   void cariArsip(char* nama) {
      Node* temp = head;
      while (temp != NULL) {
         if (strcmp(temp->data.nama, nama) == 0) {
            printf("\nArsip ditemukan: ID=%d, Nama=%s\n", temp->data.id, temp->data.nama);
            return;
         }
         temp = temp->next;
      }
      printf("\nArsip tidak ditemukan\n");
   }
   
   // Sorting (bubble sort)
   void bubbleSort() {
      Arsip arr[MAX];
      int count = 0;
      Node* temp = head;
      while (temp != NULL) {
         arr[count++] = temp->data;
         temp = temp->next;
      }
      
      for (int i = 0; i < count - 1; i++) {
         for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(arr[j].nama, arr[j + 1].nama) > 0) {
               Arsip tmp = arr[j];
               arr[j] = arr[j + 1];
               arr[j + 1] = tmp;
            }
         }
      }
      
      printf("\n--- Arsip Setelah Disorting ---\n");
      for (int i = 0; i < count; i++) {
         printf("ID: %d, Nama: %s, Tanggal: %s, Kategori: %s\n",
            arr[i].id, arr[i].nama, arr[i].tanggal, arr[i].kategori);
         }
      }
      
      // Tree untuk kategori
      typedef struct TreeNode {
         char kategori[30];
         struct TreeNode* left;
         struct TreeNode* right;
      } TreeNode;
      
      TreeNode* buatNode(char* nama) {
         TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
         strcpy(node->kategori, nama);
         node->left = node->right = NULL;
         return node;
      }
      
      void printPreOrder(TreeNode* root) {
         if (root != NULL) {
            printf("%s\n", root->kategori);
            printPreOrder(root->left);
            printPreOrder(root->right);
         }
      }
      
      
      // Menu utama
      int main() {
         TreeNode* root = buatNode("Arsip");
         root->left = buatNode("Akademik");
         root->right = buatNode("Pribadi");
         
         int idCounter = 1; 
         int pilihan;
         Arsip arsip;
         char namaCari[50];
         
         do {
            printf("\n===== Menu Arsip =====\n");
            printf("1. Tambah Arsip\n");
            printf("2. Tampilkan Arsip\n");
            printf("3. Cari Arsip\n");
            printf("4. Sorting Arsip (Nama)\n");
            printf("5. Undo Tambah Arsip\n");
            printf("6. Proses Antrian \n");
            printf("7. Tampil Antrian \n");
            printf("8. Edit Identitas Arsip (ID)\n");
            printf("9. Hapus Arsip\n");
            printf("10. Lihat Kategori\n");
            printf("0. Keluar\n");
            printf("Pilih: ");
            scanf("%d", &pilihan);
            getchar();
            
            switch (pilihan) {
               case 1:
               // Tambah Arsip
               arsip.id = idCounter++;
               printf("Nama: "); fgets(arsip.nama, 50, stdin); arsip.nama[strcspn(arsip.nama, "\n")] = '\0';
               printf("Tanggal: "); fgets(arsip.tanggal, 20, stdin); arsip.tanggal[strcspn(arsip.tanggal, "\n")] = '\0';
               printf("Kategori: "); fgets(arsip.kategori, 30, stdin); arsip.kategori[strcspn(arsip.kategori, "\n")] = '\0';
               enqueue(arsip);
               break;
               case 2:
               // Tampil Arsip
               tampilArsip();
               break;
               case 3:
               // Cari Arsip
               printf("Nama arsip yang dicari: "); fgets(namaCari, 50, stdin); namaCari[strcspn(namaCari, "\n")] = '\0';
               cariArsip(namaCari);
               break;
               case 4:  
               // Sorting Arsip  
               bubbleSort();
               break;
               case 5:
               // Undo tambah arsip
               arsip = pop();
               if (arsip.id != -1) {
                  printf("Undo arsip: %s\n", arsip.nama);
                  Node *curr = head, *prev = NULL;
                  while (curr != NULL) {
                     if (curr->data.id == arsip.id) {
                        if (prev == NULL) head = curr->next;
                        else prev->next = curr->next;
                        free(curr);
                        break;
                     }
                     prev = curr;
                     curr = curr->next;
                  }
                  enqueue(arsip);
               } else {
                  printf("Stack kosong.\n");
               }
               break;
               case 6:
               // Proses antrian arsip
               arsip = dequeue();
               if (arsip.id != -1) {
                  printf("Memproses arsip: %s\n", arsip.nama);
                  tambahArsip(arsip);
                  push(arsip);
               } else {
                  printf("Queue kosong.\n");
               }
               break;
               case 7:
               // Tampil antrian
               tampilQueue();
               break;
               case 8:
               // Edit Arsip
               editArsip();
               break;
               case 9:
               // Hapus arsip
               hapusArsip();
               break;
               case 10:
               // Tampil kategori
               printf("\n--- Kategori Arsip ---\n");
               printPreOrder(root);
               break;
            }
            
         } while (pilihan != 0);
         
         return 0;
      }
      