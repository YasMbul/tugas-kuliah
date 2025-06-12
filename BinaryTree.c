#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   char data;
   struct Node* left;
   struct Node* right;
} Node;

Node* buatSimpul(char data) {
   Node* simpul = (Node*) malloc(sizeof(Node));
   if (simpul == NULL) return simpul;
   simpul->data = data;
   simpul->left = NULL;
   simpul->right = NULL;
   return simpul;
}

char inputSimpul() {
   char c;
   while (1) {
      printf("Masukkan Simpul (ketik . jika kosong): ");
      scanf(" %c", &c);
      if (c == '.' || isalpha(c)) {
         return c;
      } else {
         printf("Input tidak valid. Hanya huruf A-Z atau . untuk kosong!\n");
      }
   }
}

Node* buatTree() {
   char data = inputSimpul();
   
   if (data == '.') {
      return NULL;
   }
   
   Node* simpul = buatSimpul(data);
   if (simpul == NULL) {
      printf("Memori Penuh!\n");
      exit(1);
   }
   printf("Masukkan anak kiri dari %c:\n", data);
   simpul->left = buatTree();
   
   printf("Masukkan anak kanan dari %c:\n", data);
   simpul->right = buatTree();
   
   return simpul;
}

// PreOrder (Akar - Kiri - Kanan)
void preOrder(Node* root) {
   if (root != NULL) {
      printf("%c ", root->data);
      preOrder(root->left);
      preOrder(root->right);
   }
}

// InOrder (Kiri - Akar - Kanan)
void inOrder(Node* root) {
   if (root != NULL) {
      inOrder(root->left);
      printf("%c ", root->data);
      inOrder(root->right);
   }
}

// PostOrder (Kiri - Kanan - Akar)
void postOrder(Node* root) {
   if (root != NULL) {
      postOrder(root->left);
      postOrder(root->right);
      printf("%c ", root->data);
   }
}

void freeTree(Node* root) {
   if (root != NULL) {
      freeTree(root->left);
      freeTree(root->right);
      free(root);
   }
}

int main() {
   system("cls");
   printf("Input binary tree:\n");
   Node* root = buatTree();
   
   if (root == NULL){
      system("cls");
      printf("Anda Tidak Menginputkan Apapun! Coba Jalankan Ulang Kode!");
      return 0;
   }
   printf("Hasil PreOrder : ");
   preOrder(root);
   printf("\n");
   
   printf("Hasil InOrder  : ");
   inOrder(root);
   printf("\n");
   
   printf("Hasil PostOrder : ");
   postOrder(root);
   printf("\n");
   
   freeTree(root);
   return 0;
}
