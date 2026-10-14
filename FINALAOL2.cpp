#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    char name[100];
    char city[100];
    int cost;
    char currency[100];
    int price_range;
    float rating;
    char rating_count[100];
    int votes;


} Restaurant;

int totalRows = 0;
Restaurant database[10000];


// fungsi baca file
void bacaFile() {
    FILE *file = fopen("Restaurant.csv", "r");
    
    if (file == NULL) {
        printf("File tidak ditemukan!\n");
        printf("Pastikan file Restaurant.csv ada di folder yang sama dengan program ini.\n");
        
//        return;
    }

    char line[512];

    // Skip the header line
    fgets(line, sizeof(line), file);

    int jumlahData = 0;


    while (fgets(line, sizeof(line), file) && jumlahData < 10000) {
        char *bagian = strtok(line, ";");
        int kolom = 0;

        strcpy(database[jumlahData].name, "");
        strcpy(database[jumlahData].city, "");
        database[jumlahData].cost = 0;
        strcpy(database[jumlahData].currency, "");
        database[jumlahData].price_range = 0;
        database[jumlahData].rating = 0.0;
        strcpy(database[jumlahData].rating_count, "");
        database[jumlahData].votes = 0;


        while (bagian != NULL && kolom < 8) {
            

            while(*bagian == ' ')
                bagian++;

            
            int panjang = strlen(bagian);
            while(panjang > 0 && (bagian[panjang - 1] == ' ' || 
                  bagian[panjang - 1] == '\n' || 
                  bagian[panjang - 1] == '\r')) {
                bagian[--panjang] = '\0';
            }

            switch (kolom) {
                case 0: // nama restoran
                    strcpy(database[jumlahData].name, bagian);
                    break;
                case 1: // kota
                    strcpy(database[jumlahData].city, bagian);
                    break;
                case 2: // cost
                    database[jumlahData].cost = atoi(bagian);
                    break;
                case 3: // currency
                    strcpy(database[jumlahData].currency, bagian);
                    break;
                case 4: // price range
                    database[jumlahData].price_range = atoi(bagian);
                    break;
                case 5: // rating
                    database[jumlahData].rating = atof(bagian);
                    break;
                case 6: // rating text
                    strcpy(database[jumlahData].rating_count, bagian);
                    break;
                case 7: // votes
                    database[jumlahData].votes = atoi(bagian);
                    break;
            }
            bagian = strtok(NULL, ";"); 
            kolom++;
        }

        jumlahData++;
    }

    fclose(file);
    totalRows = jumlahData;
    printf("\n========================================\n");
    printf("Sukses: Data berhasil dibaca!\n");
    printf("Total data restauran dalam database: %d\n", totalRows);
    printf("========================================\n\n");

}


// A. menampilkan data

void tampilanData() {
    int jumlahBaris;
    printf("\n--- Tampilkan Data Restoran ---\n");
    printf("Masukkan jumlah data yang ingin ditampilkan: ");
    scanf("%d", &jumlahBaris);

    // validasi input jumlahBaris
    if(jumlahBaris <= 0) {
        printf("Input tidak valid. Jumlah baris harus lebih dari 0.\n");
//        return;
    }

    // jika jumlahBaris lebih dari totalRows, tampilkan semua data
    if(jumlahBaris > totalRows) {
        printf("Catatan: Hanya ada %d data dalam database. Menampilkan semua data.\n", totalRows);
        jumlahBaris = totalRows;

    }

    // header tabel
    printf("\n================================================================================================================================================\n");
    printf("|| %-24s || %-16s || %-12s || %-20s || %-11s || %-6s || %-12s || %-5s ||\n", 
        "Nama Restaurant", "Kota", "Harga 2 orang", "Mata Uang", "Range Harga", "Rating", "Kategori", "Vote");
    printf("================================================================================================================================================\n");
    
    // tampilkan data
    for(int i = 0; i < jumlahBaris; i++) {
        printf("|| %-24s || %-16s || %-12d || %-20s || %-11d || %-6.1f || %-12s || %-5d ||\n", 
            database[i].name, 
            database[i].city, 
            database[i].cost, 
            database[i].currency, 
            database[i].price_range, 
            database[i].rating, 
            database[i].rating_count,
            database[i].votes);
    }
    
        printf("================================================================================================================================================\n");
        printf("\nTotal data yang ditampilkan: %d dari %d\n\n", jumlahBaris, totalRows);

}


// B. mencari data

void searchData() {
    int pilihanKolom;
    char kataKunci[100];

    printf("\n--- Cari Data Restoran ---\n");
    printf("Pilih kolom untuk pencarian:\n");
    printf("1. Name Restaurant\n");
    printf("2. City\n");
    printf("3. Kategori (Rating text)\n");
    printf("Masukkan pilihan (1-3): ");
    scanf("%d", &pilihanKolom);

    // validasi input pilihanKolom
    if(pilihanKolom < 1 || pilihanKolom > 3) {
        printf("ERROR: Pilihan harus antara 1-3.\n");
//        return;
    }

    printf("Masukkan kata kunci pencarian: ");
    getchar(); // bersihkan newline sebelumnya
    fgets(kataKunci, sizeof(kataKunci), stdin);

    // hapus newline dari kataKunci
    kataKunci[strcspn(kataKunci, "\n")] = 0;

    int ditemukan = 0;

    //header
    printf("\nHasil pencarian untuk \"%s\":\n", kataKunci);
    printf("================================================================================================================================================\n");
    printf("|| %-24s || %-16s || %-12s || %-20s || %-11s || %-6s || %-12s || %-5s ||\n", 
        "Nama Restaurant", "Kota", "Harga 2 orang", "Mata Uang", "Range Harga", "Rating", "Kategori", "Vote");
    printf("================================================================================================================================================\n");

    // cari di semua data
    for(int i = 0; i < totalRows; i++) {
        char *dataKolom;
        int cocok = 0;

        switch(pilihanKolom) {
            case 1:
                dataKolom = database[i].name;
                if(strstr(dataKolom, kataKunci) != NULL) cocok = 1;
                break;
            case 2:
                dataKolom = database[i].city;
                if(strstr(dataKolom, kataKunci) != NULL) cocok = 1;
                break;
            case 3:
                dataKolom = database[i].rating_count;
                if(strstr(dataKolom, kataKunci) != NULL) cocok = 1;
                break;
        }

        //bandingin sama kata kunci
        if(cocok) {
            printf("|| %-24s || %-16s || %-12d || %-20s || %-11d || %-6.1f || %-12s || %-5d ||\n", 
                database[i].name, 
                database[i].city, 
                database[i].cost, 
                database[i].currency, 
                database[i].price_range, 
                database[i].rating, 
                database[i].rating_count,
                database[i].votes);
            ditemukan++;

        }

    }

    printf("================================================================================================================================================\n\n");

    if(ditemukan == 0) {
        printf("\nMaaf: Data tidak ditemukan.\n");
        printf("Silakan coba kata kunci lain.\n\n");
        printf("Tips: \n");
        printf("1. Pastikan penulisan yang digunakan benar (case-sensitive).\n");
        printf("2. Cek spasi di awal atau akhir kata kunci.\n");
        printf("3. Contoh pencarian: \"KFC\", \"Bandung\", \"New Delhi\"\n");

    } else {
        printf("\nSukses: Total data ditemukan: %d\n", ditemukan);
}

    printf("\n");

}


// C. sorting data

void urutkanData() {
    int pilihanKolom;
    char urutan[10];

    printf("\n--- Urutkan Data Restoran ---\n");
    printf("Pilih kolom untuk pengurutan:\n");
    printf("1. Nama Restaurant\n");
    printf("2. Kota\n");
    printf("3. Harga (termurah-termahal atau sebaliknya)\n");
    printf("4. Rating (terendah-tertinggi atau sebaliknya)\n");
    printf("Masukkan pilihan (1-4): ");
    scanf("%d", &pilihanKolom);

    if(pilihanKolom < 1 || pilihanKolom > 4) {
        printf("ERROR: Pilihan harus antara 1-4.\n");
     
    }

    printf("Urutan [asc] untuk naik, [desc] untuk menurun: ");
    scanf("%s", urutan);

    int ascending = 1;
    if(strcmp(urutan, "desc") == 0) {
        ascending = 0;
    } else if(strcmp(urutan, "asc") != 0) {
        printf("ERROR: Gunakan 'asc' atau 'desc'.\n");
//        return;
    }

    // bubble sort
    for(int i = 0; i < totalRows - 1; i++) {
        for(int j = 0; j < totalRows - i - 1; j++) { 
            int tukar = 0;

            switch(pilihanKolom) {
                case 1: // nama restoran
                    if(ascending) {
                        if(strcmp(database[j].name, database[j+1].name) > 0) {
                            tukar = 1;
                        }
                    } else {
                        if(strcmp(database[j].name, database[j+1].name) < 0) {
                            tukar = 1;
                        }
                    }
                    break;
                case 2: // kota
                    if(ascending) {
                        if(strcmp(database[j].city, database[j+1].city) > 0) {
                            tukar = 1;
                        }
                    } else {
                        if(strcmp(database[j].city, database[j+1].city) < 0) {
                            tukar = 1;
                        }
                    }
                    break;
                case 3: // cost
                    if(ascending) {
                        if(database[j].cost > database[j+1].cost) {
                            tukar = 1;
                        }
                    } else {
                        if(database[j].cost < database[j+1].cost) {
                            tukar = 1;
                        }
                    }
                    break;
                case 4: // rating
                    if(ascending) {
                        if(database[j].rating > database[j+1].rating) {
                            tukar = 1;
                        }
                    } else {
                        if(database[j].rating < database[j+1].rating) {
                            tukar = 1;
                        }
                    }
                    break;
            }

            if(tukar) {
                Restaurant temp = database[j];
                database[j] = database[j+1];
                database[j+1] = temp;
            }
        }
    }

    printf("\nSUKSES: Data berhasil diurutkan!\n");
    printf("Menampilkan 10 data pertama:\n");

    printf("\n================================================================================================================================================\n");
    printf("|| %-24s || %-16s || %-12s || %-20s || %-11s || %-6s || %-12s || %-5s ||\n", 
        "Name Restaurant", "City", "Harga 2 orang", "Mata Uang", "Range Harga", "Rating", "Kategori", "Vote");
    printf("================================================================================================================================================\n");
    
    // tampilkan 10 data pertama
    int tampilkan = (totalRows < 10) ? totalRows : 10;
    for(int i = 0; i < tampilkan; i++) {
        printf("|| %-24s || %-16s || %-12d || %-20s || %-11d || %-6.1f || %-12s || %-5d ||\n", 
            database[i].name, 
            database[i].city, 
            database[i].cost, 
            database[i].currency, 
            database[i].price_range, 
            database[i].rating, 
            database[i].rating_count,
            database[i].votes);
    }
    
    printf("================================================================================================================================================\n\n");
}


// D. fungsi export data
void exportData() {
    char nameFile[100];

    printf("\n--- EXPORT DATA ---\n");
    printf("Masukkan nama file (tanpa .csv): ");
    scanf("%s", nameFile);

    // tambah ekstensi .csv
    char namaLengkap[200];
    sprintf(namaLengkap, "%s.csv", nameFile); 

    // buka file untuk ditulis
    FILE *fileOutput = fopen(namaLengkap, "w");
    if(fileOutput == NULL) {
        printf("Gagal membuat file %s\n", namaLengkap);
        printf("Pastikan folder dapat ditulis!\n");
        // return;
    }

    // tulis header CSV
    fprintf(fileOutput, "Name Restaurant;City;Harga 2 orang;Mata Uang;Range Harga;Rating;Kategori;Vote\n");

    // tulis semua data
    for(int i = 0; i < totalRows; i++) {
        fprintf(fileOutput, "%s;%s;%d;%s;%d;%.1f;%s;%d\n",
            database[i].name,
            database[i].city,
            database[i].cost,
            database[i].currency,
            database[i].price_range,
            database[i].rating,
            database[i].rating_count,
            database[i].votes);
    }

    fclose(fileOutput);

    printf("\n========================================\n");
    printf("Sukses: Data berhasil diexport\n");
    printf("Nama file: %s\n", namaLengkap); 
    printf("Jumlah data: %d restoran\n", totalRows);
    printf("Lokasi file: folder yang sama dengan program ini\n");
    printf("========================================\n");

}


// main menu
int main() {
    // baca data dari file
    bacaFile();

    int pilihan;
    do {
        printf("\n================ Main Menu ================\n");
        printf("1. Tampilkan Data Restoran\n");
        printf("2. Cari Data Restoran\n");
        printf("3. Urutkan Data Restoran\n");
        printf("4. Export Data ke File CSV\n");
        printf("5. Keluar dari Program\n");
        printf("===========================================\n");
        printf("Pilihan Anda (1-5): ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                tampilanData();
                break;
            case 2:
                searchData();
                break;
            case 3:
                urutkanData();
                break;
            case 4:
                exportData();
                break;
            case 5:
                printf("\nTerima kasih telah menggunakan program ini. Sampai jumpa!\n");
                printf("Program selesai....\n");
                break;
            default:
                printf("Input tidak valid. Silakan pilih antara 1-5.\n");
        }

        if(pilihan != 5) {
            printf("\nTekan Enter untuk kembali ke menu utama...");
            getchar(); // untuk bersihkan newline
            getchar(); // tunggu user tekan enter

        }

    } while(pilihan != 5);

    return 0;
}
