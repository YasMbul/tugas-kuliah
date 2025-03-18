#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <time.h> 

#define KAPASITAS 100

struct IdentitasBarang {
    char kodeBarang[KAPASITAS];
    char namaBarang[50];
    char bahanDasar[50];
    float jmlh;
    float harga;
};


void delay(int detik)
{
    // Mengubah detik menjadi milidetik
    int milidetik = 1000 * detik;

    // Mengambil waktu saat ini
    clock_t mulai = clock();

    // Ulang sampai waktu lebih dari waktu saat ini + delay
    while (clock() < mulai + milidetik);
}

void pilihMenu (int *pil){
    // int pil;
    printf("=======================================\n");
    printf("|   TUGAS DATABASE TOKO MEBEL RAMOS   |\n");
    printf("|-------------------------------------|\n");
    printf("|           1. Input Barang           |\n");
    printf("|           2. Lihat Stok             |\n");
    printf("|           3. Exit                   |\n");
    printf("|                                     |\n");
    printf("|*************************************|\n");
    printf("=======================================\n");
    printf("        Masukkan Pilihan anda : "); 
    scanf("%d", pil);
    system("cls");
}

void inputBarang(int *total, struct IdentitasBarang *Barang){
    system("cls");
    int n;
    printf("===============Input Barang===============\n\n");
    printf("Berapa banyak barang yang anda simpan : "); scanf("%d", &n);
    if(*total + n > KAPASITAS){
        printf("Inventory Penuh!");
        return;
    }
    for(int i = 1; i <= n; i++){
        printf(":: Kode Barang    : [%d] : ", *total + i); scanf("%s", &Barang[*total].kodeBarang);
        printf(":: Nama Barang    : [%d] : ", *total + i); scanf("%s", &Barang[*total].namaBarang);
        printf(":: Bahan Dasar    : [%d] : ", *total + i); scanf("%s", &Barang[*total].bahanDasar);
        printf(":: Jumlah Barang  : [%d] : ", *total + i); scanf("%f", &Barang[*total].jmlh);
        printf(":: Harga per-unit : [%d] : ", *total + i); scanf("%f", &Barang[*total].harga);
        printf("\n");
        (*total)++;
    }
    system("cls");
    printf("\n          Input berhasil!");
    delay(2);
    system("cls");
}

void tampilInventori(int *total, struct IdentitasBarang *Barang){
    printf("=============== Persediaan Barang ===============\n\n");
    for(int i = 0; i < *total; i++){
        printf("Data barang ke %d : \n", i+1);
        printf("         :: Kode Barang        : %s\n", Barang[i].kodeBarang);
        printf("         :: Nama Barang        : %s\n", Barang[i].namaBarang);
        printf("         :: Bahan Dasar        : %s\n", Barang[i].bahanDasar);
        printf("         :: Jumlah Barang      : %.1f\n", Barang[i].jmlh);
        printf("         :: Harga per-unit     : Rp. %.2f\n", Barang[i].harga);
        delay(1);
    }
    printf("Enter untuk melanjutkan");
    getchar();
    getchar();
}
void tampilInventoriKosong(){
    printf("        =============== Persediaan Barang ===============       \n\n");
    printf("  Belum ada barang yang di Input, silahkan input terlebih dahulu!\n");
    delay(5);
    system("cls");
}


void main (){
    system("cls");
    struct IdentitasBarang Barang[KAPASITAS];
    int total = 0;
    int pilihan, pil;
    do{
        pilihMenu(&pilihan);
        switch(pilihan){
            case 1 : {
                inputBarang(&total, Barang);
            }
            break;
            case 2 : {
                if (total == 0){
                    tampilInventoriKosong();
                    break;
                }
                tampilInventori(&total, Barang);
            }
            break;
            case 3 : {
                printf("Apakah anda yakin akan keluar? (1/0) "); scanf("%d", &pil);
                if (pil == 1){
                    printf("Terimakasih telah menggunakan layanan kami!");
                    break;
                }
                if (pil == 0){
                    pilihan = 1;
                    system("cls");
                }
            }
            break;
            default : {
                printf("Pilihan tidak tersedia!\n");
                delay(1);
                system("cls");
            } 
        }
    } while (pilihan != 3);
}

