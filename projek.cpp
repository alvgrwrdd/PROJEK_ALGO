#include <iostream>
#include <stdio.h>
using namespace std;

void my_strcpy(char* dest, const char* src) {
    while (*src) { *dest = *src; dest++; src++; }
    *dest = '\0';
}

bool my_strcmp(const char* s1, const char* s2) {
    while (*s1 && *s1 == *s2) { s1++; s2++; }
    return (*s1 == *s2);
}

int my_strlen(const char* s) {
    int len = 0;
    while (*s) { len++; s++; }
    return len;
}

void printPad(const char* str, int width) {
    int len = my_strlen(str);
    cout << str;
    for (int i = len; i < width; i++) cout << " ";
}

void printPadNum(int num, int width) {
    cout << num;
    int len = 1, temp = num;
    while(temp > 9) { len++; temp /= 10; }
    for(int i = len; i < width; i++) cout << " ";
}

struct Pengeluaran {
    char tanggal[20];
    char kategori[30];
    char deskripsi[50];
    double nominal;
};

struct Node {
    Pengeluaran data;
    Node* kiri;  
    Node* kanan; 
};

Node* kepala; 
Node* ekor;   

void buatList() {
    kepala = new Node;
    ekor = new Node;
    
    kepala->data.nominal = -99999;
    kepala->kanan = ekor;
    kepala->kiri = ekor; 
    
    ekor->data.nominal = 99999;
    ekor->kiri = kepala;
    ekor->kanan = kepala; 
}

bool kosong() {
    return kepala->kanan == ekor;
}

void pause() {
    cout << "\nTekan enter...";
    cin.get();
}

void clearScreen() {
    for(int i = 0; i < 30; i++) cout << "\n";
}


void tambahPengeluaran() {
    Node* baru = new Node;
    
    cout << "Tanggal (dd-mm-yyyy): ";
    cin.getline(baru->data.tanggal, 20);
    
    cout << "Kategori: ";
    cin.getline(baru->data.kategori, 30);
    
    cout << "Deskripsi: ";
    cin.getline(baru->data.deskripsi, 50);
    
    cout << "Nominal: ";
    cin >> baru->data.nominal;
    cin.ignore();
    
    
    baru->kanan = ekor;
    baru->kiri = ekor->kiri;
    ekor->kiri->kanan = baru;
    ekor->kiri = baru;
    
    cout << "\nData berhasil ditambahkan!\n";
}

void tampilkan() {
    if(kosong()){
        cout << "Data kosong.\n";
        return;
    }

    Node* bantu = kepala->kanan;
    int no = 1;

    cout << "\n===== HISTORI PENGELUARAN =====\n";
    printPad("No", 5);
    printPad("Tanggal", 15);
    printPad("Kategori", 20);
    printPad("Deskripsi", 25);
    cout << "Nominal\n";

    while(bantu != ekor) {
        printPadNum(no++, 5);
        printPad(bantu->data.tanggal, 15);
        printPad(bantu->data.kategori, 20);
        printPad(bantu->data.deskripsi, 25);
        cout << bantu->data.nominal << "\n";
        
        bantu = bantu->kanan;
    }
}

void cariKategori() {
    if(kosong()){ cout << "Data kosong.\n"; return; }

    char cari[30];
    cout << "Masukkan kategori dicari: ";
    cin.getline(cari, 30);

    Node* bantu = kepala->kanan;
    bool ketemu = false;

    while(bantu != ekor) {
        if(my_strcmp(bantu->data.kategori, cari)) {
            cout << bantu->data.tanggal << " | "
                 << bantu->data.deskripsi << " | Rp"
                 << bantu->data.nominal << "\n";
            ketemu = true;
        }
        bantu = bantu->kanan;
    }

    if(!ketemu) cout << "Tidak ditemukan.\n";
}

void hapusData() {
    if(kosong()){ cout << "Data kosong.\n"; return; }
    tampilkan();

    int hapus;
    cout << "Hapus data nomor: ";
    cin >> hapus;
    cin.ignore();

    Node* bantu = kepala->kanan;
    int pos = 1;

    while(bantu != ekor && pos < hapus) {
        bantu = bantu->kanan;
        pos++;
    }

    if(bantu == ekor) {
        cout << "Nomor tidak valid\n";
        return;
    }

    
    bantu->kiri->kanan = bantu->kanan;
    bantu->kanan->kiri = bantu->kiri;
    delete bantu;

    cout << "Data dihapus.\n";
}

void totalBulanan() {
    double total = 0;
    Node* bantu = kepala->kanan;
    while(bantu != ekor) {
        total += bantu->data.nominal;
        bantu = bantu->kanan;
    }
    cout << "Total Pengeluaran: Rp" << total << "\n";
}

void sortNominal() {
    if(kosong() || kepala->kanan->kanan == ekor){
        cout << "Data kurang untuk sorting.\n";
        return;
    }

    bool tukar;
    Node* p;
    Pengeluaran temp;

    do {
      tukar = false;
      p = kepala->kanan;

      while(p->kanan != ekor) {
          if(p->data.nominal > p->kanan->data.nominal) {
              temp = p->data;
              p->data = p->kanan->data;
              p->kanan->data = temp;
              tukar = true;
          }
          p = p->kanan;
      }
    } while(tukar);

    cout << "Data berhasil diurutkan ascending nominal.\n";
}

void clearList() {
    Node* bantu = kepala->kanan;
    while(bantu != ekor) {
        Node* hapus = bantu;
        bantu = bantu->kanan;
        delete hapus;
    }
    kepala->kanan = ekor;
    ekor->kiri = kepala;
}
