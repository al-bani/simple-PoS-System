#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h> 
#include "header.h"
#include "cake_list.c"
#define MAX_NUM 20
#define TAX 6000
#define TIME_REMAINING 1
FILE *fptr;

void wrong(){
    printf("maaf pilihan anda salah\nSilahkan tekan Enter untuk memilih kembali...\n");
    getch();
}

void menu(info cake[], info order[]){
    int i, pilih;

    awal : 
    system("cls");
    printf("================================================================================================\n");
    printf("                                       Menu Toko Kue BARCA                                    \n");
    printf("================================================================================================\n");
    printf("No.  Nama Kue\t\t      Kode Kue\t\t     Stock Kue\t\t        Harga Kue\n");
    printf("================================================================================================\n");
    
    for (i = 1; i<=MAX_NUM; i++){
        printf("%d %s\t\t\t%s\t\t\t%d\t\t\tRp. %d\n",i, cake[i].name_cake, cake[i].code_cake, cake[i].jumlah_cake, cake[i].harga_cake);
    }
    printf("================================================================================================\n");
    printf("1. Sorting secara Ascending harga\n2. Lanjut Ke Pemesanan\n");  
    printf("================================================================================================\n");
    printf("Pilihan anda : ");scanf("%d", &pilih);
    if (pilih == 1){
       sorting(cake);
    } else if (pilih > 2){
        wrong();
        goto awal;
    }
    
}

void sorting(info cake[]){
    int i,j;
    int temp_harga, temp_jumlah;
    char temp_name[100], temp_code[100];

    for (i=1; i<= MAX_NUM; i++){
        for (j=1; j <= MAX_NUM-i; j++){
            if (cake[j].harga_cake > cake[j+1].harga_cake){
               temp_harga = cake[j].harga_cake;
               cake[j].harga_cake = cake[j+1].harga_cake;
               cake[j+1].harga_cake = temp_harga;

               temp_jumlah = cake[j].jumlah_cake;
               cake[j].jumlah_cake = cake[j+1].jumlah_cake;
               cake[j+1].jumlah_cake = temp_jumlah;

               strcpy(temp_name, cake[j].name_cake);
               strcpy(cake[j].name_cake, cake[j+1].name_cake);
               strcpy(cake[j+1].name_cake, temp_name);

               strcpy(temp_code, cake[j].code_cake);
               strcpy(cake[j].code_cake, cake[j+1].code_cake);
               strcpy(cake[j+1].code_cake, temp_code);
            }
        }
    }

    system("cls");
    printf("=================================================================================================\n");
    printf("                          Menu Toko Kue BARCA - Sort Ascending Harga                             \n");
    printf("=================================================================================================\n");
    printf("No.  Nama Kue\t\t      Kode Kue\t\t     Stock Kue\t\t        Harga Kue\n");
    printf("=================================================================================================\n");
    
    for (i = 1; i<=MAX_NUM; i++){
        printf("%d  %s\t\t\t%s\t\t\t%d\t\t\tRp. %d\n",i, cake[i].name_cake, cake[i].code_cake, cake[i].jumlah_cake, cake[i].harga_cake);
    }
    printf("=================================================================================================\n");
}

void place_order(info cake[], info order[]){
    struct customer cust;
    int n,i, pilih;
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("Masukkan Jumlah orderan kue : ");  scanf("%d", &n);
    printf("-------------------------------------------------------------------------------------------------\n");

    awal :
    printf("=================================================================================================\n");
    for (i = 1; i <= n; i++){
       printf("\nMasukkan Nomer kue ke [%d] yang dipilih (1-20) : ",i);  scanf("%d", &order[i].no_cake);
       if (order[i].no_cake > MAX_NUM ){
           wrong();
           goto awal;
           break;
       }
       printf("Masukkan Jumlah kue %s :  ", cake[order[i].no_cake].name_cake);  scanf("%d", &order[i].jumlah_cake);
       if (order[i].jumlah_cake > cake[order[i].no_cake].jumlah_cake){
           printf("Maaf anda membeli kue melebih stok yang kami punya!\ntekan enter untuk kembali");
           getch();
           goto awal;
           break;
       }

       cake[i].jumlah_cake -= order[i].jumlah_cake;
       strcpy(order[i].name_cake, cake[order[i].no_cake].name_cake);
       strcpy(order[i].code_cake, cake[order[i].no_cake].code_cake);
       order[i].harga_cake = cake[order[i].no_cake].harga_cake;
    }

    informasi(cust, n, pilih, order, cake);
}

void informasi(struct customer cust,int n, int pilih, info order[], info cake[]){
    struct payment pay;
    taking tk[2];

    system("cls");
    printf("=================================================================\n");
    printf("                       Informasi data pelanggan                  \n");
    printf("=================================================================\n");
    printf("   Data Diri\n");
        printf("    Nama                   : ");                   fgetc(stdin); gets(cust.name_cust);
        printf("    umur                   : ");                   scanf("%d", &cust.age_cust); fgetc(stdin);
        printf("    Email                  : ");                  gets(cust.email_cust);
        printf("    No HP (start with 62)  : ");                  scanf("%d", &cust.phone_cust);  fgetc(stdin);
    printf("=================================================================\n");
    printf("   Alamat                            \n");
        printf("    Provinsi               : ");         gets(cust.addr.prov); 
        printf("    Kota                   : ");             gets(cust.addr.city);
        printf("    Alamat                 : ");   gets(cust.addr.full_addr);
        printf("    Kode POS               : ");         scanf("%d", &cust.addr.zip_code);
    printf("=================================================================\n");

    
    cetak_informasi(cust);

    pilih :
    system("cls");
    printf("==================\n");
    printf("pengambilan kue\n1. Diambil\n2. Diantar\n");
    printf("Masukan pilihan anda : ");   scanf("%d", &pilih);

    switch (pilih){
    case 1:
       diambil(pilih, pay, tk);
       order_info(cake, order, n,pay, tk);
        break;
    case 2:
        diantar(pilih, pay);
        order_info(cake, order, n,pay, tk);
        break;
    default:
    wrong();
    goto pilih;
        break;
    }
}

taking *diambil(int pilih, struct payment pay, taking tk[]){
    pay.ewallet = 0;
    pay.mbank = 0;
    pay.cod = 0;
    tk[0].take = 1;

    int random = rand();

    pilihan :
    system("cls");
    printf("======================\n");
    printf("Metode Pembayaran\n");
    printf("======================\n");
    printf("1. E-Wallet\n");
    printf("2. M-Banking\n");
    printf("======================\n");
    printf("Masukkan pilihan anda : ");  scanf("%d", &pilih);
    
    switch (pilih){
    case 1:
    pay.ewallet = random;
        break;
    case 2:
    pay.mbank = random;
        break;
    default:
    wrong();
    goto pilihan;
        break;
    }

    return tk;
}

void diantar(int pilih, struct payment pay){
    pay.ewallet = 0;
    pay.mbank = 0;
    pay.cod = 0;

    int random = rand();

    pilihan :
    system("cls");
    printf("=========================\n");
    printf("    Metode Pembayaran  \n");
    printf("=========================\n");
    printf("1. E-Wallet\n");
    printf("2. M-Banking\n");
    printf("3  COD\n");
    printf("=========================\n");
    printf("Masukkan pilihan anda : ");  scanf("%d", &pilih);

    switch (pilih){
        case 1:
            pay.ewallet = random;
        break;
        case 2:
            pay.mbank = random;
        break;
        case 3:
            pay.cod = random;
        break;
        default:
            wrong();
        goto pilihan;

        break;
    }
}

void order_info(info cake[], info order[], int n, struct payment pay, taking tk[]){
    int total, pilih, keseluruhan = 0;

    awal :
    system("cls");
    printf("================================================================================\n");
    printf("                            Pesanan Anda                           \n");
    printf("================================================================================\n");
    printf("No.  Nama Kue\t\tKode Kue\t  Stock Kue \t\tHarga Kue\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 1; i<=n; i++){
        printf("%d  %s\t\t%s\t\t     %d\t\t        Rp. %d\n",i, order[i].name_cake, order[i].code_cake, order[i].jumlah_cake, order[i].harga_cake);
        keseluruhan += (order[i].harga_cake * order[i].jumlah_cake);
    }

   printf("================================================================================\n");
    printf("\nTotal harga : Rp. %d", keseluruhan);
    printf("\nFee         : Rp. %d", TAX);
    printf("\n================================================================================\n");
    total = (TAX + keseluruhan);
    printf("\nTotal Keseluruhan yang harus dibayar : Rp. %d \n", total);
    printf("================================================================================\n");

    cetak_pesanan(order,n);
    printf("================================================================================\n");
    printf("\n\n1. Lanjutkan\n2. Cari data\n3. Edit data\n"); 
    printf("--------------------------------------------------------------------------------\n");
    printf("Pilihan anda : ");  scanf("%d", &pilih);

    if (pilih == 1){
        pay_info(total, pay, tk);
    } else if (pilih == 2) {
        search(order, n);
        printf("\nTekan Enter untuk melanjutkan...\n");
        getch();
        pay_info(total, pay, tk);
    } else if (pilih == 3){
        kembali :
        system("cls");
        printf("========================\n");
        printf("1. Update Pesanan\n");
        printf("2. Hapus Pesanan\n");
        printf("0. kembali\n");
        printf("========================\n");
        printf("Masukkan pilihan anda : ");  scanf("%d", &pilih);

        if (pilih == 1){
            update(cake, order,n, pay, tk);
        } else if (pilih == 2){
            if (n <= 1){
                printf("Maaf anda tidak bisa menghapus pesanan\nkarena anda hanya mempunyai satu pesanan\nSilahkan update pesanan untuk menambahkan pesanan");
                printf("\nTekan enter untuk kembali\n");
                getch();
                goto kembali;
            }
            delete(cake, order,n, pay,tk);
        } else if(pilih == 0){
            goto awal;
        } else {
            wrong();
            goto awal;
        }
    } else {
    wrong();
    goto awal;
    }
}

void pay_info(int total, struct payment pay, taking tk[]){
    int kode_pembayaran;

    system("cls");
    printf("==================================\n");
    printf("           Pembayaran\n");
    printf("==================================\n");

    printf("Total Nominal yang dibayar : %d\n",total);

    if (pay.cod != 0){
        kode_pembayaran = pay.cod;
    } else if (pay.ewallet != 0){
        kode_pembayaran = pay.ewallet;
    } else if (pay.mbank != 0){
        kode_pembayaran = pay.mbank;
    }
    printf("==================================\n");
    printf("Kode Pembayaran : PAY-%d\n", kode_pembayaran);
    printf("tenggat Waktu pembayaran : %d jam\n", TIME_REMAINING);
    printf("==================================\n");

    printf("\n\nEnter untuk Melanjutkan\n");
    getch();

    success(total,pay, tk);
}

void search(info order[], int n){
    char cari[100];
    printf("\nMasukan kue yang ingin dicari : ");  getc(stdin);
    gets(cari);
    printf("================================================================================\n");
    printf("No.  Nama Kue\t\tKode Kue\t  Stock Kue \t\tHarga Kue\n");
    printf("================================================================================\n");
    for (int i = 1; i <= n; i++){
        if (strstr(order[i].name_cake,cari)!=NULL){
           printf("%d  %s\t\t%s\t\t     %d\t\t        Rp. %d\n",i, order[i].name_cake, order[i].code_cake, order[i].jumlah_cake, order[i].harga_cake);

        }
    }
}

void cetak_informasi(struct customer cust){
    int i;

    fptr = fopen("informasi_pelanggan.txt", "w");
    
    fprintf(fptr,"informasi Pelanggan");
    fprintf(fptr,"\nNama            : %s ",cust.name_cust);
    fprintf(fptr,"\nUmur            : %d ",cust.age_cust);
    fprintf(fptr,"\nEmail           : %s ",cust.email_cust);
    fprintf(fptr,"\nNomor telepon   : %d ",cust.phone_cust);

    fprintf(fptr,"\nAddress");
    fprintf(fptr,"\n\tProvinsi         : %s ",cust.addr.prov);
    fprintf(fptr,"\n\tKota             : %s ",cust.addr.city);
    fprintf(fptr,"\n\tAlamat lengkap   : %s ",cust.addr.full_addr);
    fprintf(fptr,"\n\tKode POS         : %d ",cust.addr.zip_code);
    
    fclose(fptr);
}

void cetak_pesanan(info order[], int n){
    int i;

    fptr = fopen("data_pesanan.txt", "w");
    
    for(i = 1; i <= n; i++){
        fprintf(fptr,"Pesanan ke [%d]", i);
        fprintf(fptr,"\nNama Kue             : %s ",order[i].name_cake);
        fprintf(fptr,"\nKode Kue             : %s ",order[i].code_cake);
        fprintf(fptr,"\nJumlah kue dipesan   : %d ",order[i].jumlah_cake);
        fprintf(fptr,"\nHarga kue            : %d \n\n",order[i].harga_cake);
    }

    fclose(fptr);
}

void update (info cake[], info order[], int n, struct payment pay, taking tk[]){
    int pilih, i, temp = n, tambah, j;
    system("cls");
    printf("===================\n");
    printf("update Pesanan\n1. Tambah Pesanan\n0. Kembali\n");
    printf("===================\n");
    printf("Masukkan pilihan anda : "); scanf("%d", &pilih);

    switch (pilih){
    case 1:
        awal :
        n = temp;
        tambah = 0;
        j = n;
    printf("=================================================================================================\n");
    printf("                          Menu Toko Kue BARCA - Sort Ascending Harga                             \n");
    printf("=================================================================================================\n");
    printf("No.  Nama Kue\t\t      Kode Kue\t\t     Stock Kue\t\t        Harga Kue\n");
    printf("=================================================================================================\n");
    
        for (i = 1; i<=MAX_NUM; i++){
            printf("%d  %s\t\t\t%s\t\t\t%d\t\t\tRp. %d\n",i, cake[i].name_cake, cake[i].code_cake, cake[i].jumlah_cake, cake[i].harga_cake);
        }

        printf("\nMasukkan Jumlah Pesanan yang ditambah : "); scanf("%d", &tambah);

        for (i = 1; i <= tambah; i++){
            j += 1;
            
            printf("\nMasukkan Nomer kue ke [%d] yang dipilih (1-20) : ", i);  scanf("%d", &order[j].no_cake);

            if (order[j].no_cake > MAX_NUM ){
                wrong();
                goto awal;
                break;
            }

            printf("Masukkan Jumlah kue %s :  ", cake[order[j].no_cake].name_cake);  scanf("%d", &order[j].jumlah_cake);
            if (order[j].jumlah_cake > cake[order[j].no_cake].jumlah_cake){
                printf("Maaf anda membeli kue melebih stok yang kami punya!\ntekan enter untuk kembali");
                getch();
                goto awal;
                break;
            }

            cake[order[j].jumlah_cake].jumlah_cake -= order[j].jumlah_cake;

            strcpy(order[j].name_cake, cake[order[j].no_cake].name_cake);
            strcpy(order[j].code_cake, cake[order[j].no_cake].code_cake);
            order[j].harga_cake = cake[order[j].no_cake].harga_cake;
        }
        n = n + tambah;

        system("cls");
        
        printf("data tersimpan !\n");
        printf("==============\n");
        printf("1. Lanjutkan\n2. Tambah lagi\n");
        printf("==============\n");
        printf("Masukkan pilihan : ");  scanf("%d", &pilih);

        if (pilih == 1){
            order_info(cake,order,n,pay, tk);
        } else if(pilih == 2){
            goto awal;
        } else {
            wrong();
            goto awal;
        }
        break;
     case 0:
        order_info(cake,order,n,pay, tk);
        break;
    default:
    wrong();
    goto awal;
        break;
    }
}

void delete(info cake[], info order[], int n, struct payment pay, taking tk[]){
    int i,hapus, pilih;
    
    awal :
    system("cls");
    printf("================================================================================\n");
    printf("                            Hapus Pesanan                  \n");
    printf("================================================================================\n");
    printf("No.  Nama Kue\t\tKode Kue\t  Stock Kue \t\tHarga Kue\n");
    printf("---------------------------------------------------------------------------------\n");
    for ( i = 1; i<=n; i++){
        printf("%d  %s\t\t%s\t\t     %d\t\t        Rp. %d\n",i, order[i].name_cake, order[i].code_cake, order[i].jumlah_cake, order[i].harga_cake);
    }
    printf("================================================================================\n");
    printf("\nHapus pesanan Nomor : ");  scanf("%d", &hapus);

    for (i = 1; i <= n; i++){   
        if (hapus == i){
            strcpy(order[n+10].name_cake, order[i].name_cake);
            strcpy(order[n+10].code_cake, order[i].code_cake);
            order[n+10].jumlah_cake = order[i].jumlah_cake;
            order[n+10].harga_cake = order[i].harga_cake;
        }
    }

    for (i = hapus; i <= n; i++){
        strcpy(order[i].name_cake, order[i+1].name_cake);
        strcpy(order[i].code_cake, order[i+1].code_cake);
        order[i].jumlah_cake = order[i+1].jumlah_cake;
        order[i].harga_cake = order[i+1].harga_cake;
    }

    n = n-1;
    printf("\nData Tersimpan !\n");

    if (n <= 1){
        printf("Tekan enter untuk Melanjutkan\n");
        getch();
        order_info(cake,order,n,pay, tk);
    } else if (n > 1){
        printf("=====================\n");
        printf("1. Hapus Pesanan lagi\n2. Lanjut Checkout\n");
        printf("=====================\n"); 
        printf("Masukkan pilihan anda : "); scanf("%d", &pilih);

        if (pilih == 1){
            goto awal;
        } else if (pilih == 2){
            order_info(cake,order,n,pay, tk);
        }
    }
    
}

int success(int total, struct payment pay, taking tk[]){
    int max=1,min=0, l = 9;

    srand(time(0)); 
    while(l>0){
        max*=9;
        l--;
    }
    min=max/9;

    printf(" %d ", min + rand() % (max - min));
    system("cls");
    printf("==================================\n");
    printf("\tRincian Pembayaran\n");
    printf("==================================\n");
    printf("Rp. %d\n",total);

    printf("No Order : KUE-%d", min + rand() % (max - min));
    
    if (tk[0].take == 1){
        printf("\nJadwal Pengambilan : 9AM - 5PM, 21 September 2022");
    }
    
    printf("\n----------------------------------\n");
    printf("Status : Berhasil :)");
    printf("\n----------------------------------\n");
    printf("\n");
    printf("===================================\n");
    printf("   TERIMAKASIH SUDAH BERBELANJA\n");
    printf("===================================\n");
}
