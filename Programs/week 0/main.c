
#include <stdio.h>
#include <stdlib.h>

void countCharactersWordsLines(FILE *file, int *charCount, int *wordCount, int *lineCount) {
    char ch;
    *charCount = *wordCount = *lineCount = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*charCount)++;

        if (ch == ' ' || ch == '\t' || ch == '\n') {
            if (*charCount > 1) {
                (*wordCount)++;
            }
            if (ch == '\n') {
                (*lineCount)++;
            }
        }
    }

    if (*charCount > 0) {
        (*wordCount)++;
        (*lineCount)++;
    }
}

int main() {
    FILE *file1, *file2;
    char line[100];

    file1 = fopen("studentout1.dat", "w");
    if (file1 == NULL) {
        printf("Error\n");
        return 1;
    }

    fprintf(file1, "Implementing data structures would be fun.\n");
    fclose(file1);

    file1 = fopen("studentout1.dat", "r");
    if (file1 == NULL) {
        printf("Error\n");
        return 1;
    }

    printf("\nContent of studentout1.dat:\n");
    while (fgets(line, sizeof(line), file1) != NULL) {
        printf("%s", line);
    }

    fclose(file1);

    file1 = fopen("studentout1.dat", "a");
    if (file1 == NULL) {
        printf("Error\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        printf("\nEnter line to append: ");
        fgets(line, sizeof(line), stdin);
        fprintf(file1, "%s", line);
    }

    fclose(file1);

    file1 = fopen("studentout1.dat", "r");
    file2 = fopen("studentout2.dat", "w");

    if (file1 == NULL || file2 == NULL) {
        printf("Error\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file1) != NULL) {
        fprintf(file2, "%s", line);
    }

    fclose(file1);
    fclose(file2);

    file2 = fopen("studentout2.dat", "r");

    if (file2 == NULL) {
        printf("Error\n");
        return 1;
    }

    int charCount, wordCount, lineCount;
    countCharactersWordsLines(file2, &charCount, &wordCount, &lineCount);

    printf("\nCharacter count in studentout2.dat: %d\n", charCount);
    printf("Word count in studentout2.dat: %d\n", wordCount);
    printf("Line count in studentout2.dat: %d\n", lineCount);

    fclose(file2);

    return 0;
}
