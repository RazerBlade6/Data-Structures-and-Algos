#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SCANSTR(str) scanf("%[^\n]%*c",str)

typedef struct Student {
    char name[50];
    char id[14];
    double cgpa;
} STUDENT;

typedef struct Node {
    STUDENT entry;
    STUDENT *next;
} NODE;

typedef struct LinkedList {
    NODE *data;
    int pointer;
    int size;
} LINKEDLIST;

void insert(LINKEDLIST*, int, char[], char[], double);
int find(LINKEDLIST, char []);
int delete(LINKEDLIST*, char []);
static inline STUDENT get(LINKEDLIST, int);
static inline void display(LINKEDLIST);
static inline int size(LINKEDLIST);
static inline int isEmpty(LINKEDLIST);

int main() {
    LINKEDLIST linkedlist;
    STUDENT student;
    
    linkedlist.pointer = 0;
    linkedlist.size = 1;

    linkedlist.data = (NODE *)malloc(linkedlist.size * sizeof(NODE));

    FILE *file = fopen("studentin.dat","r");
    if (file == NULL) {
        perror("Error");
        return 1;
    }

    while (fscanf(file, "%s %s %lf", student.name, student.id, &student.cgpa) == 3) {
        insert(&linkedlist, linkedlist.pointer, student.name, student.id, student.cgpa);
    }
    linkedlist.data[linkedlist.pointer].next = (STUDENT *)NULL;

    fclose(file);

    int choice, position, result;
    char name[50];
    char id[14];
    double cgpa;

    while (1) {
        printf("Welcome to the Linked List Interface\n");
        printf("0. Clear the Screen\n1. Add a record\n2. Find a record by name\n3. Delete a record\n");
        printf("4. Get a record by index\n5. Display the list\n6. Check if Empty\n7. Get the Size\n8. Exit\n");
        printf("Choice: ");
        scanf("%d",&choice);

        switch (choice) {
            case 0:
                system("cls");
                break;
                
            case 1:
                printf("Enter the position to insert to (-1 for last position): ");
                scanf("%d", &position);
                if (position == -1)
                position = linkedlist.pointer;
                fflush(stdin);

                printf("Enter the Name: ");
                SCANSTR(name);

                printf("Enter the ID: ");
                SCANSTR(id);

                printf("Enter the CGPA: ");
                scanf("%lf", &cgpa);

                insert(&linkedlist, position, name, id, cgpa);
                linkedlist.data[linkedlist.pointer].next = (STUDENT *)NULL;

                break;
            case 2:
                fflush(stdin);
                printf("Enter the Name to search: ");
                SCANSTR(name);
                result = find(linkedlist, name);
                if (result == -1) {
                    printf("%s is not present in the list.\n", name);
                } else {
                    printf("%s is found at %d.\n", name, result);
                }
                break;

            case 3:
                fflush(stdin);
                printf("Enter the Name to be deleted: ");
                SCANSTR(name);

                result = delete(&linkedlist, name);
                if (result < 0) {
                    printf("%s not found, cannot be deleted.\n", name);
                } else {
                    printf("%s deleted from list index %d.\n", name, result);
                    linkedlist.data[linkedlist.pointer].next = (STUDENT *)NULL;
                }
                break;
            
            case 4:
                printf("Enter the index to find: ");
                scanf("%d", &position);

                student = get(linkedlist, position);

                printf("Name: %s, ID: %s, CGPA: %lf\n", student.name, student.id, student.cgpa);
                break;
            
            case 5:
                display(linkedlist);
                break;

            case 6:
                if (isEmpty(linkedlist)) {
                    printf("Linked List is Empty\n");
                } else {
                    printf("Not Empty\n");
                }
                break;

            case 7:
                printf("Size of linked List is: %d\n", size(linkedlist));
                break;
                
            case 8:
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }
}

void insert(LINKEDLIST *linkedlist, int position, char name[], char ID[], double cgpa) {
    
    if (position > linkedlist->pointer){
        printf("Cannot Add Elements At indices beyond size of the linked list");
        return;
    } else {
        linkedlist->data = (NODE *)realloc(linkedlist->data, ++linkedlist->size * sizeof(NODE));
    }
    
    STUDENT student;
    strcpy(student.name, name);
    strcpy(student.id, ID);
    student.cgpa = cgpa;
    
    for (int i = linkedlist->pointer - 1; i >= position; i--) {
        linkedlist->data[i + 1] = linkedlist->data[i];
    }
    linkedlist->pointer++;
    linkedlist->data[position].entry = student;
    linkedlist->data[position].next = &linkedlist->data[position + 1].entry;
}

int find(LINKEDLIST linkedlist, char name[]) {
    for (int i = 0; i < linkedlist.pointer; i++) {
        if (!strcmp(linkedlist.data[i].entry.name, name)) {
            return i;
        }
    }

    return -1;
}

int delete(LINKEDLIST *linkedlist, char name[]) {
    int index = find(*linkedlist, name);
    if (index == -1)
        return -1;
    
    for (int i = index + 1; i < linkedlist->pointer; i++) {
        linkedlist->data[i - 1] = linkedlist->data[i];
    }
    
    linkedlist->pointer--;
    return index;
}

static inline STUDENT get(LINKEDLIST linkedlist, int position) {
    return linkedlist.data[position].entry;
}

static inline void display(LINKEDLIST linkedlist) {
    STUDENT student;

    for (int i = 0; linkedlist.data[i].next != NULL; ++i) {
        student = linkedlist.data[i].entry;
        printf("%d. Name: %s, ID: %s, CGPA: %lf\n", i + 1, student.name, student.id, student.cgpa);
    }
}

static inline int size(LINKEDLIST linkedlist) {
    return linkedlist.pointer;
}

static inline int isEmpty(LINKEDLIST linkedlist) {
    return (!linkedlist.pointer) ? 1 : 0;
}
