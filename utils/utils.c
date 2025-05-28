#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include "hashmap.h"

uint64_t int_hash(const void *item, uint64_t seed0, uint64_t seed1)
{
    int key = *(const int *)item;
    // simple integer hashing, can be improved
    return hashmap_murmur((const void *)&key, sizeof(int), seed0, seed1);
}

int int_compare(const void *a, const void *b, void *udata)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);  // returns 1, -1 or 0
}

int hexDigit(char c) {
    c = toupper(c); // permettre maj et min
    switch(c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return c-'0';
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F': return c-'A'+10;
        default: // signaler une erreur
    }
    return -1;
}