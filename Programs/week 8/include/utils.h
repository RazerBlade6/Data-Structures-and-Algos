#ifndef UTILS_HASH_TABLE
#define UTILS_HASH_TABLE

#define true 1
#define false 0
#include <string.h>
#include <stdio.h>

typedef unsigned long long uint64_t;

#define get_string(x) \
    fgets(x, 255, stdin); \
    x[strcspn(x, "\n")] = '\0'

int validate_uint(char *integer) {
    for (uint64_t i = 0; i < strlen(integer); i++) {
        if (integer[i] < '0' || integer[i] > '9')
        return false;
    }
    return true;
}

#endif 