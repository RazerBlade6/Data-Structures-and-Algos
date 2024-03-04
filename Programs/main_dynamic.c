#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

typedef struct Search {
    int searchedElement;
    int position;
    double runtime;
} SEARCH;

SEARCH linearSearch(int *arr, int size, int key);
SEARCH binarySearch(int *arr, int size, int key);

int main() {
    FILE *file = fopen("testCaseSize.txt", "r");

    if (file == NULL) {
        printf("Error, File Not Found\n");
        return 1;
    }

    int index, num[15], i = 0;

    printf("Enter the element to read from the file: ");

    scanf("%d", &index);
    index--;

    while (fscanf(file, "%d", &num[i]) == 1) {
        i++;
    }

    fclose(file);
    printf("The element at line %d is %d\n\n", index + 1, num[index]);

    int key;
    printf("Enter the Element you would like to search: ");
    scanf("%d", &key);

    FILE *searchfile = fopen("searchTestCase.txt", "r");

    if (searchfile == NULL) {
        printf("Error, File Not Found\n");
        return 1;
    }

    int *arr;
    int size = 1;
    index = 0;

    arr = (int *)malloc(size * sizeof(int));

    while (fscanf(searchfile, "%d", &arr[index]) == 1) {
        ++index;
        arr = (int *)realloc(arr, ++size * sizeof(int));
    }

    fclose(searchfile);

    clock_t t = clock();
    quickSort(arr, 0, index - 1);
    t = (clock() - t);
    printf("Quick Sort Time: %lf\n", (double)(t * 1000));

    SEARCH linear = linearSearch(arr, index, key);
    if (linear.searchedElement != -1) {
        printf("Linear Search Results: Element: %d, Position: %d, Runtime: %lf\n", linear.searchedElement, linear.position, linear.runtime);
    } else {
        printf("Linear Search Results: Element: %d, Position: Not Found, Runtime: %lf\n", linear.searchedElement, linear.runtime);
    }
    SEARCH binary = binarySearch(arr, index, key);
    if (binary.searchedElement != -1) {
        printf("Binary Search Results: Element: %d, Position: %d, Runtime: %lf\n", binary.searchedElement, binary.position, binary.runtime);
    } else {
        printf("Binary Search Results: Element: %d, Position: Not Found, Runtime: %lf\n", binary.searchedElement, binary.runtime);
    }
    FILE *linfile = fopen("linearSearchResults.txt", "w");
    FILE *binfile = fopen("binarySearchResults.txt", "w");

    fprintf(linfile, "Results of All Test Cases for Linear Search are:\n");
    fprintf(binfile, "Results of All Test Cases for Binary Search are:\n");

    for (i = 0; i < 15; i++) {
        key = num[i];

        SEARCH testlinear = linearSearch(arr, size, key);
        SEARCH testbinary = binarySearch(arr, size, key);
        if (testlinear.searchedElement != -1) {
            fprintf(linfile, "Element: %d, Position: %d, Runtime: %lf ms\n", testlinear.searchedElement, testlinear.position, testlinear.runtime);
        } else {
            fprintf(linfile, "Element: %d, Position: Not Found, Runtime: %lf ms\n", testlinear.searchedElement, testlinear.runtime);
        }
        if (testbinary.searchedElement != -1) {
            fprintf(binfile, "Element: %d, Position: %d, Runtime: %lf ms\n", testbinary.searchedElement, testbinary.position, testbinary.runtime);
        } else {
            fprintf(binfile, "Element: %d, Position: Not Found, Runtime: %lf ms\n", testbinary.searchedElement, testbinary.runtime);
        }
    }

    fclose(linfile);
    fclose(binfile);
    free(arr);

    return 0;
}

SEARCH linearSearch(int *arr, int size, int key) {
    clock_t t = clock();
    int index = -1;

    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            index = i;
            break;
        }
    }
    t = clock() - t;

    SEARCH linear = {key, index, (double)(t * 1000)};
    return linear;
}

SEARCH binarySearch(int *arr, int size, int key) {
    clock_t t = clock();
    int index = -1;

    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            index = mid;
            break;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    t = clock() - t;

    SEARCH binary = {key, index, (double)(t * 1000)};
    return binary;
}
