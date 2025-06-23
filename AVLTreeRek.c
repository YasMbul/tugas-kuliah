#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node* left;
   struct Node* right;
   int height;
} Node;

// Fungsi utilitas
int max(int a, int b) {
   return (a > b) ? a : b;
}

int getHeight(Node* node) {
   if (node == NULL)
   return 0;
   return node->height;
}

int getBalance(Node* node) {
   if (node == NULL)
   return 0;
   return getHeight(node->left) - getHeight(node->right);
}

Node* buatSimpul(int data) {
   Node* simpul = (Node*) malloc(sizeof(Node));
   if (simpul == NULL) return simpul;
   simpul->data = data;
   simpul->left = NULL;
   simpul->right = NULL;
   simpul->height = 1;
   return simpul;
}

// Rotasi kanan
Node* rotasiKanan(Node* y) {
   Node* x = y->left;
   Node* T2 = x->right;
   
   x->right = y;
   y->left = T2;
   
   y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
   x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
   
   return x;
}

// Rotasi kiri
Node* rotasiKiri(Node* x) {
   Node* y = x->right;
   Node* T2 = y->left;
   
   y->left = x;
   x->right = T2;
   
   x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
   y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
   
   return y;
}

// Menyisipkan angka ke AVL Tree
Node* insertAVL(Node* root, int data) {
   if (root == NULL)
   return buatSimpul(data);
   
   if (data < root->data)
   root->left = insertAVL(root->left, data);
   else if (data > root->data)
   root->right = insertAVL(root->right, data);
   else
   return root; // duplikat diabaikan
   
   root->height = 1 + max(getHeight(root->left), getHeight(root->right));
   
   int balance = getBalance(root);
   
   // 4 kasus rotasi
   if (balance > 1 && data < root->left->data)
   return rotasiKanan(root);
   
   if (balance < -1 && data > root->right->data)
   return rotasiKiri(root);
   
   if (balance > 1 && data > root->left->data) {
      root->left = rotasiKiri(root->left);
      return rotasiKanan(root);
   }
   
   if (balance < -1 && data < root->right->data) {
      root->right = rotasiKanan(root->right);
      return rotasiKiri(root);
   }
   
   return root;
}

// Fungsi input angka
int inputAngka() {
   int n;
   while (1) {
      printf("Masukkan angka (atau -1 untuk selesai): ");
      if (scanf("%d", &n) == 1) return n;
      else {
         printf("Input tidak valid! Masukkan angka.\n");
         while (getchar() != '\n'); // bersihkan buffer
      }
   }
}

void preOrder(Node* root) {
   if (root != NULL) {
      printf("%d ", root->data);
      preOrder(root->left);
      preOrder(root->right);
   }
}

void inOrder(Node* root) {
   if (root != NULL) {
      inOrder(root->left);
      printf("%d ", root->data);
      inOrder(root->right);
   }
}

void postOrder(Node* root) {
   if (root != NULL) {
      postOrder(root->left);
      postOrder(root->right);
      printf("%d ", root->data);
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
   printf("AVL Tree dengan Input Angka\n");
   printf("Masukkan angka satu per satu. Gunakan -1 untuk berhenti.\n");
   
   Node* root = NULL;
   while (1) {
      int data = inputAngka();
      if (data == -1) break;
      root = insertAVL(root, data);
   }
   
   if (root == NULL) {
      printf("Tidak ada data dimasukkan!\n");
      return 0;
   }
   
   printf("\nTraversal PreOrder  : ");
   preOrder(root);
   printf("\n");
   
   printf("Traversal InOrder   : ");
   inOrder(root);
   printf("\n");
   
   printf("Traversal PostOrder : ");
   postOrder(root);
   printf("\n");
   
   freeTree(root);
   return 0;
}
