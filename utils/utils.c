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