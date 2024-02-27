#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Search {
    int searchedElement;
    int position;
    double runtime;
} SEARCH;

SEARCH linearSearch(int *arr, int size, int key);
SEARCH binarySearch(int arr[], int size, int key);
void quickSort(int arr[], int low, int high);
void swap(int *a, int *b);

int main() {

    FILE *file = fopen("testCaseSize.txt","r");

    if (file == NULL) {
        printf("Error\n");
        return 1;
    }

    printf("Enter the element to read from the file: ");
    int index, num[16], i = 0;
    int key;
    scanf("%d", &index);

    while (fscanf(file, "%d", &num[i]) == 1) {
        i++;
    }

    fclose(file);
    printf("The element at line %d is %d\n\n", index + 1, num[index]);

    printf("Enter the Element you would like to search:\n");
    scanf("%d",&key);

    FILE *searchfile = fopen("searchTestCase.txt","r");

    int *arr = NULL;
    int maxSize = 983041;
    int size = 0;
    arr = (int*)malloc(maxSize * sizeof(int));
    while (fscanf(searchfile, "%d", &arr[size]) == 1) {
        size++;
        if (size > maxSize) {
            printf("Increase MaxSize again");
            exit(1);
        }
    }

    fclose(searchfile);

    quickSort(arr, 0, size - 1);

    SEARCH linear = linearSearch(arr, size, key);
    printf("Linear Search Results: Element: %d, Position: %d, Runtime: %lf\n",linear.searchedElement, linear.position, linear.runtime);
    SEARCH binary = binarySearch(arr, size, key);
    printf("Binary Search Results: Element: %d, Position: %d, Runtime: %lf\n",binary.searchedElement, binary.position, binary.runtime);

    FILE *linfile = fopen("linearSearchResults.txt","w");
    FILE *binfile = fopen("binarySearchResults.txt","w");

    fprintf(linfile,"\nResults of All Test Cases for Linear Search are:\n");
    fprintf(binfile,"\nResults of All Test Cases for Binary Search are:\n");


    for (i = 0; i < 16; i++) {
        key = num[i];

        SEARCH testlinear = linearSearch(arr, size, key);
        SEARCH testbinary = binarySearch(arr, size, key);

        fprintf(linfile,"Linear Search Results: Element: %d, Position: %d, Runtime: %lf s\n",testlinear.searchedElement, testlinear.position, testlinear.runtime);
        fprintf(binfile,"Binary Search Results: Element: %d, Position: %d, Runtime: %lf s\n",testbinary.searchedElement, testbinary.position, testbinary.runtime);
    }

    fclose(linfile);
    fclose(binfile);
    free(arr);
    
    return 0;
}

SEARCH linearSearch(int *arr, int size, int key) {
    int index = -1;
    clock_t t;

    t = clock();
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            index = i;
            break;
        }
    }
    t = clock() - t;
    SEARCH linear = {key, index, (double)t};
    return linear;
}

SEARCH binarySearch(int arr[], int size, int key) {
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
    SEARCH binary = {key, index, (double)t};
    return binary;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int leftPivot, rightPivot;

        if (arr[low] > arr[high]) {
            swap(&arr[low], &arr[high]);
        }

        leftPivot = arr[low];
        rightPivot = arr[high];

        int i = low + 1, k = low + 1, j = high - 1;

        while (k <= j) {
            if (arr[k] < leftPivot) {
                swap(&arr[i], &arr[k]);
                i++;
            } else if (arr[k] >= rightPivot) {
                while (arr[j] > rightPivot && k < j) {
                    j--;
                }

                swap(&arr[k], &arr[j]);
                j--;
                if (arr[k] < leftPivot) {
                    swap(&arr[i], &arr[k]);
                    i++;
                }
            }
            k++;
        }
        i--;
        j++;

        swap(&arr[low], &arr[i]);
        swap(&arr[high], &arr[j]);

        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, j - 1);
        quickSort(arr, j + 1, high);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
