#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // batas jumlah barang yang bisa dimasukkan

struct Item
{
    int kode; 
    char nama[50];
    char bahan[50];
    int jumlah;
    float harga;
};

// function untuk input barang
void inputBarang(struct Item *items, int *n){
    // variabel untuk menampung banyak barang yang dinputkan
    int input = 0; 
    printf("\t\t\t-- INPUT BARANG --\n\n");
    printf("Banyaknya Barang yang akan anda masukkan : ");
    scanf("%d", &input);

    // mengecek apakah barang sudah penuh atau belum
    if(*n + input > MAX){
        printf("Barang Penuh");
        return;
    }

    // looping untuk input data barang 
    for (int i = 0; i < input; i++){
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
        // menambah jumlah barang setelah user menginputkan data barang
        (*n)++;
    }
    system("cls");
    printf("%d Data Berhasil Ditambahkan\n", input);
}

// function untuk menampilkan barang yang sudah diinput
void tampilBarang(struct Item *items, int n){
    // mengecek persediaan barang
    if (n == 0){
        printf("Belum ada persediaan barang. Tambahkan terlebih dahulu\n");
        return;

    }

    printf("\t\t\t-- Persediaan Barang --\n\n");
    // looping untuk menampilkan barang
    for (int i = 0; i < n; i++){
        printf("Data Barang ke %d\n", i + 1);
        printf("\t:: Kode Barang    : %d\n", items[i].kode);
        printf("\t:: Nama Barang    : %s\n", items[i].nama);
        printf("\t:: Bahan Dasar    : %s\n", items[i].bahan);
        printf("\t:: Jumlah         : %d\n", items[i].jumlah);
        printf("\t:: Harga Per Unit : Rp. %.2f\n", items[i].harga);
        printf("\n");

    }
}


int main(){
    system("cls");
    int n = 0;
    struct Item items[MAX];
    
    int pil;
    do {
        printf("+===================================================================+\n");
        printf("                TUGAS DATABASE TOKO MEBEL RAMOS\n");
        printf("+===================================================================+\n");
        printf("|                                                                   |\n");        
        printf("|                        [MENU PILIHAN]                             |\n");        
        printf("|                        1. Input Barang                            |\n");        
        printf("|                        2. Lihat Stok Barang                       |\n");        
        printf("|                        3. Exit                                    |\n");        
        printf("|                                                                   |\n");        
        printf("+===================================================================+\n");        
        printf("                        Masukkan Pilihan : ");
        scanf("%d", &pil);
        
        switch(pil){
            case 1 : {
                system("cls");
                inputBarang(items, &n);
            }
            break;

            case 2: {
                system("cls");
                tampilBarang(items, n);
            }
            break;
            case 3: printf("Terimakasih\n");
            break;
            default : printf("Tidak Valid\n");
        }
    } while (pil != 3);
    return 0;

}
