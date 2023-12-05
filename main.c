#include "header.h"
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "windows.h"
#include "body.c"

int main(){
    info cake[100], order[100];
    struct customer cust;
    int home, pilih,n, status = 0;

    menu :
    system("cls");
        printf("==================================\n");
        printf(" SELAMAT DATANG DI TOKO KUE BARCA \n");
        printf("==================================\n");
        printf("1.Tampilkan Menu\n");
        printf("2.Deskripsi Toko\n");
        printf("3.Exit\n");
        printf("==================================\n");    
        printf("Masukkan pilihan (1-3) : ");     scanf("%d",&home);
        system("cls");
        switch (home){
            case 1:
                info_kue(cake);
                menu(cake,order);
                place_order(cake,order);
            break;

            //deskripsi
            case 2:
                printf("=====================================================================================================================================\n");
                printf("                                                       ~ Deksripsi Toko ~                                                            \n");
                printf("=====================================================================================================================================\n");
                printf("Toko kue BARCA merupakan salah satu toko yang menjual produk kue tradisional dan jajanan pasar, Toko kami telah buka sejak tahun 1989\n");
                printf("Toko Kami Buka dari Pukul : 8:00 - 22:00\n");
                printf("\n");
                printf("=====================================================================================================================================\n");
                printf("Alamat     : JL. Ahmad Yani NO 52, Bandung Timur\n");
                printf("Telp       : (021) 888291\n");
                printf("Kode Pos   : 152102      \n");
                printf("=====================================================================================================================================\n");
                printf("1. kembali ke halaman\n0. keluar : "); scanf("%d", &pilih);

                if (pilih == 1){
                    goto menu;
                    system ("cls");
                } else if(pilih == 0) {
                    system("cls");
                    exit(1);
                }
            break;

            case 3:
               exit(1);
            break;
             
            default:
                printf("maaf pilihan anda tidak sesuai !\n");
                printf("tekan Enter untuk Kembali ");
                getch();
                goto menu;
            break;
        }

}
