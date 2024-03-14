#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Student {
    char id[14];
    char name[50];
    int year;
    double cgpa;
} STUDENT;

void merge(STUDENT *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    STUDENT L[n1], R[n2];

    for (i = 0; i < n1; i++)
    L[i] = arr[left + i];

    for (j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].name, R[j].name) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(STUDENT *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
        
    }
}

int main() {

    FILE *file = fopen("studentin.dat","r");

    STUDENT student;
    int size = 1;
    int index = 0;
    STUDENT *arr = (STUDENT *)malloc(size * sizeof(STUDENT));

    while (fscanf(file,"%s %s %d %lf",student.id, student.name, &student.year, &student.cgpa) == 4) {
        arr = (STUDENT *)realloc(arr, ++size * sizeof(STUDENT));
        arr[index++] = student;
    }
    clock_t t = clock();
    mergeSort(arr, 0, index - 1);
    t = clock() - t;

    printf("Sort Time: %lf\n", (double)t/CLOCKS_PER_SEC);
    for (int i = 0; i < index; i++) {
        student = arr[i];
        printf("%d. ID: %s   NAME: %s   Year: %d   CGPA: %.2f  \n",i + 1, student.id, student.name, student.year, student.cgpa);
    }
    return 0;
}