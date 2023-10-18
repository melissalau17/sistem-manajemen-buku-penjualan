#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Buku {
    char kode[11];   // Untuk kode buku, 10 karakter + null terminator
    char nama[100];
    char jenis[50];
    float harga;
};

struct Transaksi {
    struct Buku buku;
    int jumlah;
    float totalHarga;
};

// Fungsi untuk menambah data buku dengan validasi
void inputBuku(struct Buku *buku, int *jumlahBuku) {
    int valid = 0;  // Variable untuk melacak apakah input valid

    while (!valid) {  // Loop sampai input valid
        printf("Kode Buku (10 angka): ");
        scanf("%s", buku[*jumlahBuku].kode);

        if (strlen(buku[*jumlahBuku].kode) != 10) {
            printf("\033[1;31mKode buku harus terdiri dari 10 angka.\033[0m\n");
        } else {
            valid = 1;  // Input valid, keluar dari loop
        }
    }

    valid = 0;  // Reset validasi untuk pertanyaan berikutnya

    while (!valid) {
        printf("Nama Buku: ");
        scanf(" %99[^\n]", buku[*jumlahBuku].nama);

        if (strlen(buku[*jumlahBuku].nama) == 0) {
            printf("\033[1;31mNama buku harus diisi.\033[0m\n");
        } else {
            valid = 1;  // Input valid, keluar dari loop
        }
    }

    valid = 0;  // Reset validasi untuk pertanyaan berikutnya

    while (!valid) {
        printf("Jenis Buku: ");
        scanf(" %s", buku[*jumlahBuku].jenis);

        int is_valid = 1;
        for (int i = 0; buku[*jumlahBuku].jenis[i] != '\0'; i++) {
            if (buku[*jumlahBuku].jenis[i] >= '0' && buku[*jumlahBuku].jenis[i] <= '9') {
                is_valid = 0; // Jika ada angka, maka tidak valid
                break;
            }
        }

        if (is_valid) {
            valid = 1;
        } else {
            printf("\033[1;31mJenis buku harus berupa string tanpa angka.\033[0m\n");
        }
    }

    valid = 0;  // Reset validasi untuk pertanyaan berikutnya

    while (!valid) {
        printf("Harga Buku (di atas 10000): ");
        float harga;
        scanf("%f", &harga);

        if (harga <= 10000) {
            printf("\033[1;31mHarga buku harus berupa angka di atas 10000.\033[0m\n");
        } else {
            buku[*jumlahBuku].harga = harga;
            (*jumlahBuku)++;
            printf("\033[1;32mData buku berhasil ditambahkan.\033[0m\n");
            valid = 1;  // Input valid, keluar dari loop
        }
    }
}

// Fungsi untuk menambahkan riwayat penjualan
void addTransaksi(struct Transaksi *transaksi, struct Buku *buku, int *jumlahTransaksi, int *jumlahBuku) {
    if (*jumlahBuku == 0) {
        printf("\033[1;31mBelum ada data buku. Tidak dapat melakukan penjualan.\033[0m\n");
        return;
    }

    if (*jumlahTransaksi >= 100) {
        printf("\033[1;31mMaaf, kapasitas riwayat penjualan sudah penuh.\033[0m\n");
        return;
    }

    struct Transaksi transaksiBaru;
    printf("Pilih buku yang akan dijual (masukkan indeks): ");
    int indeksBuku;
    scanf("%d", &indeksBuku);

    if (indeksBuku < 1 || indeksBuku > *jumlahBuku) {
        printf("\033[1;31mIndeks buku tidak valid.\033[0m\n");
        return;
    }

    // Salin data buku ke transaksi
    transaksiBaru.buku = buku[indeksBuku - 1];

    printf("Jumlah yang dijual: ");
    scanf("%d", &transaksiBaru.jumlah);

    if (transaksiBaru.jumlah <= 0) {
        printf("\033[1;31mJumlah penjualan harus lebih dari 0.\033[0m\n");
        return;
    }

    // Hitung total harga
    transaksiBaru.totalHarga = transaksiBaru.jumlah * transaksiBaru.buku.harga;

    transaksi[*jumlahTransaksi] = transaksiBaru;
    (*jumlahTransaksi)++;
    printf("\033[1;32mTransaksi berhasil ditambahkan.\033[0m\n");
}

// Fungsi untuk menampilkan data buku
void viewBuku(struct Buku *buku, int jumlahBuku) {
    if (jumlahBuku == 0) {
        printf("\033[1;31mBelum ada data buku.\033[0m\n");
    } else {
        for (int i = 0; i < jumlahBuku; i++) {
            printf("Index %d:\n", i + 1);
            printf("Kode Buku: %s\n", buku[i].kode);
            printf("Nama Buku: %s\n", buku[i].nama);
            printf("Jenis Buku: %s\n", buku[i].jenis);
            printf("Harga Buku: %.2f\n", buku[i].harga);
            printf("\n");
        }
    }
}

// Fungsi untuk menampilkan riwayat penjualan
void viewHistory(struct Transaksi *transaksi, int jumlahTransaksi) {
    if (jumlahTransaksi == 0) {
        printf("\033[1;31mBelum ada riwayat penjualan.\033[0m\n");
    } else {
        for (int i = 0; i < jumlahTransaksi; i++) {
            printf("Transaksi %d:\n", i + 1);
            printf("Kode Buku: %s\n", transaksi[i].buku.kode);
            printf("Nama Buku: %s\n", transaksi[i].buku.nama);
            printf("Jumlah: %d\n", transaksi[i].jumlah);
            printf("Total Harga: %.2f\n", transaksi[i].totalHarga);
            printf("\n");
        }
    }
}

// Fungsi untuk menghapus riwayat penjualan
void deleteHistory(struct Transaksi *transaksi, int *jumlahTransaksi) {
    if (*jumlahTransaksi == 0) {
        printf("\033[1;31mTidak ada riwayat penjualan yang dapat dihapus.\033[0m\n");
        return;
    }

    printf("Riwayat Penjualan saat ini:\n");
    viewHistory(transaksi, *jumlahTransaksi); // Menampilkan riwayat penjualan sebelum penghapusan

    int indeks;
    printf("Masukkan indeks riwayat penjualan yang akan dihapus: ");
    scanf("%d", &indeks);

    if (indeks >= 1 && indeks <= *jumlahTransaksi) {
        for (int i = indeks - 1; i < *jumlahTransaksi - 1; i++) {
            transaksi[i] = transaksi[i + 1];
        }
        (*jumlahTransaksi)--;
        printf("\033[1;32mRiwayat penjualan berhasil dihapus.\033[0m\n");
    } else {
        printf("\033[1;31mIndeks tidak valid.\033[0m\n");
    }
}

// Fungsi untuk menghapus data buku
void deleteBuku(struct Buku *buku, int *jumlahBuku) {
     if (*jumlahBuku == 0) {
        printf("\033[1;31mTidak ada data buku yang dapat dihapus.\033[0m\n");
        return;
    }
    
    int index;
    printf("Index data yang akan dihapus: ");
    scanf("%d", &index);
    if (index >= 1 && index <= *jumlahBuku) {
        for (int i = index - 1; i < *jumlahBuku - 1; i++) {
            buku[i] = buku[i + 1];
        }
        (*jumlahBuku)--;
        printf("\033[1;32mData buku berhasil dihapus.\033[0m\n");
    } else {
        printf("\033[1;31mIndeks tidak valid.\033[0m\n");
    }
}

int main() {
    struct Buku buku[100];
    int jumlahBuku = 0;
    struct Transaksi transaksi[100];
    int jumlahTransaksi = 0;

    int choice;
    
    puts("___________________________________");
    puts("\033[1;34mSISTEM MANAJEMEN BUKU DAN PENJUALAN\033[0m");
    puts("-----------------------------------");

    do {
        printf("Silahkan pilih salah satu dari Menu:\n");
        printf("1. Input Data Buku\n");
        printf("2. Lakukan Transaksi\n");
        printf("3. View History Penjualan\n");
        printf("4. View Data Buku\n");
        printf("5. Delete History Penjualan\n");
        printf("6. Delete Data Buku\n");
        printf("7. Exit\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputBuku(buku, &jumlahBuku);
                break;
            case 2:
                addTransaksi(transaksi, buku, &jumlahTransaksi, &jumlahBuku);
                break;
            case 3:
                viewHistory(transaksi, jumlahTransaksi);
                break;
            case 4:
                viewBuku(buku, jumlahBuku);
                break;
            case 5:
                deleteHistory(transaksi, &jumlahTransaksi);
                break;
            case 6:
                deleteBuku(buku, &jumlahBuku);
                break;
            case 7:
	            // Tambahkan kode untuk menyimpan data buku ke dalam file
	            FILE *file = fopen("databuku.txt", "w");
	            if (file == NULL) {
	                printf("Gagal membuka file databuku.txt\n");
	                exit(1); // Anda dapat menambahkan penanganan kesalahan lainnya sesuai kebutuhan
	            }
	        
	            for (int i = 0; i < jumlahBuku; i++) {
	                fprintf(file, "%s|%s|%s|%.2f\n", buku[i].kode, buku[i].nama, buku[i].jenis, buku[i].harga);
	            }
	        
	            fclose(file);
	        
	            printf("Data berhasil disimpan. Program selesai.\n");
	            exit(0); // Keluar dari program
	            break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (choice != 7);

    return 0;
}
