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
