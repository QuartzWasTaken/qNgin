#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t int_hash(const void *item, uint64_t seed0, uint64_t seed1);
int int_compare(const void *a, const void *b, void *udata);