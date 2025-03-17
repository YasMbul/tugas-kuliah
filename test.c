#include <stdio.h>
#include <stdlib.h>

#define MAX_BARANG 100  // Maksimal jumlah barang

typedef struct {
    int kode;
    char nama[50];
    char bahan[50];
    int jumlah;
    float harga;
} Item;

// Fungsi untuk input barang
void inputBarang(Item *items, int *n) {
    int jumlahInput;
    
    printf("\t\t\t-- INPUT BARANG --\n\n");
    printf("Banyaknya Barang yang akan anda masukkan : ");
    scanf("%d", &jumlahInput);

    if (*n + jumlahInput > MAX_BARANG) {
        printf("Jumlah barang melebihi kapasitas maksimal!\n");
        return;
    }

    for (int i = 0; i < jumlahInput; i++) {
        printf(":: Kode Barang      : [%d] : ", *n + 1);
        scanf("%d", &items[*n].kode);
        printf(":: Nama Barang      : [%d] : ", *n + 1);
        scanf("%s", items[*n].nama);
        printf(":: Bahan Dasar      : [%d] : ", *n + 1);
        scanf("%s", items[*n].bahan);
        printf(":: Jumlah           : [%d] : ", *n + 1);
        scanf("%d", &items[*n].jumlah);
        printf(":: Harga Per Unit   : [%d] : Rp. ", *n + 1);
        scanf("%f", &items[*n].harga);
        printf("\n");

        (*n)++;
    }
}

// Fungsi untuk menampilkan barang
void tampilBarang(Item *items, int n) {
    if (n == 0) {
        printf("Belum ada persediaan barang. Tambahkan terlebih dahulu.\n");
        return;
    }

    printf("\n\t\t\t-- Persediaan Barang --\n\n");
    for (int i = 0; i < n; i++) {
        printf("Data Barang ke-%d\n", i + 1);
        printf(":: Kode Barang    : %d\n", items[i].kode);
        printf(":: Nama Barang    : %s\n", items[i].nama);
        printf(":: Bahan Dasar    : %s\n", items[i].bahan);
        printf(":: Jumlah         : %d\n", items[i].jumlah);
        printf(":: Harga Per Unit : Rp. %.2f\n", items[i].harga);
        printf("-------------------------\n");
    }
}

int main() {
    system("cls");

    Item items[MAX_BARANG];  // Array statis dengan batas maksimal
    int n = 0;  // Menyimpan jumlah barang saat ini
    int pil;

    do {
        printf("\nMENU:\n");
        printf("1. Input Barang\n");
        printf("2. Tampilkan Barang\n");
        printf("3. Keluar\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &pil);

        switch (pil) {
            case 1:
                inputBarang(items, &n);
                break;
            case 2:
                tampilBarang(items, n);
                break;
            case 3:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pil != 3);

    return 0;
}
