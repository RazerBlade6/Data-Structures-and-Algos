#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned long long int uint64_t;

void swap(char **str1, char **str2) {
    char *temp  =  *str1;
         *str1  =  *str2;
         *str2  =  temp;
}

int compare(const char *arg1, const char *arg2) {
    return strcmp(arg1, arg2);
}

void heapify(char **array, size_t size, uint64_t index) {
    
    uint64_t root  = index;
    uint64_t left  = 2 * index + 1;
    uint64_t right = 2 * index + 2;

    if (left < size && compare(array[left], array[root]) > 0) {
        root = left;
    }

    if (right < size && compare(array[right], array[root]) > 0) {
        root = right;
    }

    if (root != index) {
        swap(&array[root], &array[index]);
        heapify(array, size, root);
    }
}

void heap_sort(char **array, size_t size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }
    
    for (int i = size - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

void print_array(char **array, size_t size) {
    for (uint64_t i = 0; i < size; i++) {
        printf("%s ", array[i]);
    }
    printf("\nSize: %lld\n", size);
}

int main() {

    char **array = malloc(sizeof(char*));

    char input[] = "#$BiT, Raj1, Boy2, 1Kind, &zebra, Gate2, joKe1, poKer3, tRicK4, 3Dial, 1RoaD, QueeN7";
    char *token = strtok(input, ", ");

    uint64_t i;
    for (i = 0; token != NULL; i++) {
        array[i] = token;
        token = strtok(NULL, ", ");
    }
    print_array(array, i);
    heap_sort(array, i);
    puts("------------------------------------------------------");
    print_array(array, i);
}