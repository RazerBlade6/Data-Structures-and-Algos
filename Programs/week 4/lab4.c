#include <stdio.h>
#include <stdlib.h>

typedef struct search {
    int searchedElement;
    int position;
    time_t time;
} SEARCH;

SEARCH linearSearch();
SEARCH binarySearch();

int main() {
    FILE *file = fopen("testCaseSize.txt","r");
    printf("Enter the element to read from the file: ");
    int index, num, i = 0;
    scanf("%d", &index);
    while(fscanf(file,"%d",&num) && i < index) {
        num()
    }
    printf("%d",num);
    return 0;
}