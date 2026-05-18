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
