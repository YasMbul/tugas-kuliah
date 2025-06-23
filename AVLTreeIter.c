#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node* kiri;
   struct Node* kanan;
   int tinggi;
   struct Node* parent; 
} Node;

int max(int a, int b) {
   return (a > b) ? a : b;
}

int tinggi(Node* n) {
   return (n ? n->tinggi : 0);
}

int balanceFactor(Node* n) {
   return (n ? tinggi(n->kiri) - tinggi(n->kanan) : 0);
}

Node* rotasiKanan(Node* x) {
   Node* y = x->kiri;
   Node* T2 = y->kanan;
   
   y->kanan = x;
   x->kiri = T2;
   
   y->parent = x->parent;
   x->parent = y;
   if (T2) T2->parent = x;
   
   x->tinggi = max(tinggi(x->kiri), tinggi(x->kanan)) + 1;
   y->tinggi = max(tinggi(y->kiri), tinggi(y->kanan)) + 1;
   
   return y;
}

Node* rotasiKiri(Node* x) {
   Node* y = x->kanan;
   Node* T2 = y->kiri;
   
   y->kiri = x;
   x->kanan = T2;
   
   y->parent = x->parent;
   x->parent = y;
   if (T2) T2->parent = x;
   
   x->tinggi = max(tinggi(x->kiri), tinggi(x->kanan)) + 1;
   y->tinggi = max(tinggi(y->kiri), tinggi(y->kanan)) + 1;
   
   return y;
}

// Fungsi iteratif insert AVL
Node* AVL(Node* root, int data) {
   Node* baru = (Node*) malloc(sizeof(Node));
   baru->data = data;
   baru->kiri = baru->kanan = baru->parent = NULL;
   baru->tinggi = 1;
   
   if (!root) return baru;
   
   Node* current = root;
   Node* parent = NULL;
   
   // Telusuri Tree
   while (current) {
      parent = current;
      if (data < current->data)
      current = current->kiri;
      else if (data > current->data)
      current = current->kanan;
      else {
         free(baru); // Duplikat
         return root;
      }
   }
   
   // Masukkan Node ke Tree
   baru->parent = parent;
   if (data < parent->data)
   parent->kiri = baru;
   else
   parent->kanan = baru;
   
   // Perbarui tinggi & rotasi 
   current = baru;
   while (current) {
      current->tinggi = 1 + max(tinggi(current->kiri), tinggi(current->kanan));
      int balance = balanceFactor(current);
      
      //  Rotasi jika tidak balance
      if (balance > 1) {
         if (data < current->kiri->data) {
            // Left-Left 
            if (!current->parent) {
               root = rotasiKanan(current);
            } else {
               if (current->parent->kiri == current)
               current->parent->kiri = rotasiKanan(current);
               else
               current->parent->kanan = rotasiKanan(current);
            }
         } else {
            // Left-Right 
            current->kiri = rotasiKiri(current->kiri);
            if (!current->parent)
            root = rotasiKanan(current);
            else {
               if (current->parent->kiri == current)
               current->parent->kiri = rotasiKanan(current);
               else
               current->parent->kanan = rotasiKanan(current);
            }
         }
         break;
      }
      
      if (balance < -1) {
         if (data > current->kanan->data) {
            // Right-Right 
            if (!current->parent) {
               root = rotasiKiri(current);
            } else {
               if (current->parent->kiri == current)
               current->parent->kiri = rotasiKiri(current);
               else
               current->parent->kanan = rotasiKiri(current);
            }
         } else {
            // Rigth-Left
            current->kanan = rotasiKanan(current->kanan);
            if (!current->parent)
            root = rotasiKiri(current);
            else {
               if (current->parent->kiri == current)
               current->parent->kiri = rotasiKiri(current);
               else
               current->parent->kanan = rotasiKiri(current);
            }
         }
         break;
      }
      current = current->parent;
   }
   
   return root;
}

void preOrder(Node* root) {
   if (root != NULL) {
      printf("%d ", root->data);
      preOrder(root->kiri);
      preOrder(root->kanan);
   }
}

void inOrder(Node* root) {
   if (root != NULL) {
      inOrder(root->kiri);
      printf("%d ", root->data);
      inOrder(root->kanan);
   }
}

void postOrder(Node* root) {
   if (root != NULL) {
      postOrder(root->kiri);
      postOrder(root->kanan);
      printf("%d ", root->data);
   }
}

void freeTree(Node* root) {
   if (root != NULL) {
      freeTree(root->kiri);
      freeTree(root->kanan);
      free(root);
   }
}

int input() {
   int n;
   while (1) {
      printf("Masukkan angka (-1 untuk berhenti): ");
      if (scanf("%d", &n) == 1) return n;
      else {
         printf("Input tidak valid!\n");
         while (getchar() != '\n');
      }
   }
}

int main() {
   system("cls");
   printf("AVL Tree\n");
   
   Node* root = NULL;
   while (1) {
      int data = input();
      if (data == -1) break;
      root = AVL(root, data);
   }
   
   if (!root) {
      printf("Anda Tidak Menginputkan Data Apapun!\n");
      return 0;
   }
   
   // printf("\nPreOrder  : "); preOrder(root);
   printf("\nInOrder   : "); inOrder(root);
   // printf("\nPostOrder : "); postOrder(root);
   printf("\n");
   
   freeTree(root);
   return 0;
}
