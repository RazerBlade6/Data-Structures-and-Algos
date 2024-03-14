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

void swap(STUDENT *a, STUDENT *b) {
    STUDENT temp = *a;
    *a = *b;
    *b = temp;
}

int partition(STUDENT *arr, int low, int high) {
  
    STUDENT pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (strcmp(arr[j].name, pivot.name) < 0) {
        i++;
        swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(STUDENT *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    quickSort(arr, 0, index - 1);

    for (int i = 0; i < index; i++) {
        student = arr[i];
        printf("%d. ID: %s   NAME: %s   Year: %d   CGPA: %.2f  \n",i + 1, student.id, student.name, student.year, student.cgpa);;
    }
    return 0;
}