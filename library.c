#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
} Book;

void kitapEkle() {
    FILE *fp = fopen("books.dat", "ab");
    if (fp == NULL) {
        printf("Dosya olusturulamadi!\n");
        return;
    }

    Book yeniKitap;
    printf("Kitap ID: ");
    scanf("%d", &yeniKitap.id);
    getchar();

    printf("Kitap Adi: ");
    fgets(yeniKitap.title, sizeof(yeniKitap.title), stdin);
    yeniKitap.title[strcspn(yeniKitap.title, "\n")] = 0;

    printf("Yazar Adi: ");
    fgets(yeniKitap.author, sizeof(yeniKitap.author), stdin);
    yeniKitap.author[strcspn(yeniKitap.author, "\n")] = 0;

    printf("Basim Yili: ");
    scanf("%d", &yeniKitap.year);

    fwrite(&yeniKitap, sizeof(Book), 1, fp);
    fclose(fp);

    printf("Kitap eklendi!\n");
}

void kitapListele() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("Henüz kitap bulunmamaktadır.\n");
        return;
    }

    Book b;
    printf("\n--- Kitap Listesi ---\n");
    while (fread(&b, sizeof(Book), 1, fp)) {
        printf("ID: %d\n", b.id);
        printf("Adi: %s\n", b.title);
        printf("Yazar: %s\n", b.author);
        printf("Yil: %d\n", b.year);
        printf("-------------------------\n");
    }

    fclose(fp);
}

void kitapAra() {
    int aranacakID;
    int bulundu = 0;

    printf("Aramak istediginiz kitap ID'sini girin: ");
    scanf("%d", &aranacakID);

    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    Book b;
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (b.id == aranacakID) {
            printf("Kitap bulundu!\n");
            printf("ID: %d\n", b.id);
            printf("Adi: %s\n", b.title);
            printf("Yazar: %s\n", b.author);
            printf("Yil: %d\n", b.year);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu)
        printf("Kitap bulunamadi.\n");

    fclose(fp);
}

void kitapSil() {
    int silinecekID;
    int bulundu = 0;

    printf("Silmek istediginiz kitap ID'sini girin: ");
    scanf("%d", &silinecekID);

    FILE *fp = fopen("books.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Dosya acilamadi.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    Book b;
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (b.id != silinecekID) {
            fwrite(&b, sizeof(Book), 1, temp);
        } else {
            bulundu = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("books.dat");
    rename("temp.dat", "books.dat");

    if (bulundu)
        printf("Kitap silindi.\n");
    else
        printf("Kitap bulunamadi.\n");
}

int main() {
    const char correctUsername[] = "admin";
    const char correctPassword[] = "1234";

    char username[50];
    char password[50];
    int loginSuccess = 0;

    printf("Kullanici adi: ");
    scanf("%s", username);

    printf("Sifre: ");
    scanf("%s", password);

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        loginSuccess = 1;
        printf("Giris basarili!\n");
    } else {
        printf("Hatali kullanici adi veya sifre.\n");
    }

    if (loginSuccess==0) {
        printf("Program kapatiliyor.\n");
        return 0;
    }

    int secim;

    do {
        printf("\n--- Kütüphane Yönetim Sistemi ---\n");
        printf("1. Kitap Ekle\n");
        printf("2. Kitap Ara\n");
        printf("3. Tüm Kitaplari Listele\n");
        printf("4. Kitap Sil\n");
        printf("5. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kitapEkle();
                break;
            case 2:
                kitapAra();
                break;
            case 3:
                kitapListele();
                break;
            case 4:
                kitapSil();
                break;
            case 5:
                printf("Programdan cikiliyor.\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }

    } while (secim != 5);

    return 0;
}
