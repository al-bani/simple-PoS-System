#ifndef header
#define header

typedef struct{
    char name_cake[100];
    char code_cake[100];
    int jumlah_cake;
    int harga_cake;
    int no_cake;
}info;

struct address{
    char prov[100];
    char city[100];
    char full_addr[100];
    int zip_code;
};

struct customer{
    char name_cust[100];
    char email_cust[100];
    int phone_cust;
    int age_cust;
    struct address addr;
};

struct payment{
    int ewallet;
    int mbank;
    int cod;
};

typedef struct{
    int take;
}taking;



void menu(info cake[], info order[]);
void place_order(info cake[], info order[]);
void informasi(struct customer cust, int n, int pilih, info order[], info cake[]);
taking *diambil(int pilih, struct payment pay, taking tk[]);
void diantar(int pilih,struct payment pay);
void order_info(info order[],info cake[], int n, struct payment pay, taking tk[]);
void pay_info(int total, struct payment pay, taking tk[]);
void sorting(info cake[]);
void search(info order[], int n);
void cetak_pesanan(info order[], int n);
void cetak_informasi(struct customer cust);
int success(int total, struct payment pay,taking tk[]);
void wrong();
void update(info cake[], info order[], int n, struct payment pay, taking tk[]);
void delete(info cake[], info order[], int n, struct payment pay, taking tk[]);


#endif