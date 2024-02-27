#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10

typedef struct Student {
    char id[14];
    char name[50];
    char dob[50];
    double cgpa;
} STUDENT;

typedef struct Node {
    STUDENT entry;
    STUDENT *prev;
    STUDENT *next;
} NODE;

typedef struct LinkedList {
    NODE data[CAPACITY];
    int pointer;
} LINKEDLIST;

void addElement(LINKEDLIST*, NODE, STUDENT);
void removeElement(LINKEDLIST*, int index);
void traverseForward(LINKEDLIST);
void traverseBackward(LINKEDLIST);

int main() {
    LINKEDLIST linkedlist;
    linkedlist.pointer = 0;
    STUDENT student;
    FILE *file = fopen("studentin.dat", "r");
    while (fscanf(file,"%s %s %s %lf",student.id, student.name, student.dob, &student.cgpa) == 4) {
        addElement(&linkedlist, linkedlist.data[linkedlist.pointer], student);
    }

    for (int i = 0; i < linkedlist.pointer; i++) {
        printf("Entry in Linked List: ID: %s, Name: %s, DOB: %s, CGPA: %.2lf\n", linkedlist.data[i].entry.id, linkedlist.data[i].entry.name, linkedlist.data[i].entry.dob, linkedlist.data[i].entry.cgpa);
    }

    int index;
    printf("Enter the index to remove: ");
    scanf("%d", &index);
    removeElement(&linkedlist, index);
    traverseForward(linkedlist);
    traverseBackward(linkedlist);
    return 0;
}

void addElement(LINKEDLIST *linkedlist, NODE node, STUDENT student) {
    if(linkedlist->pointer == CAPACITY) {
        printf("Linked List Overflow\n");
    }
    node.entry = student;
    if (linkedlist->pointer-1 > -1)
    node.prev = &linkedlist->data[linkedlist->pointer - 1].entry;
    if (linkedlist->pointer + 1 < CAPACITY - 1)
    node.next = &linkedlist->data[linkedlist->pointer + 1].entry;

    linkedlist->data[linkedlist->pointer] = node;
    linkedlist->pointer++;
}

void removeElement(LINKEDLIST *linkedlist, int index) {
    if (index > linkedlist->pointer || index < 0) {
        printf("\nNo element at index %d\n", index);
        return;
    }

    for (int i = index + 1; i < linkedlist->pointer; i++) {
        linkedlist->data[i-1] = linkedlist->data[i];
    }
    linkedlist->pointer--;
}

void traverseForward(LINKEDLIST linkedlist) {
    printf("\nTraversal in Forward Direction:\n");
    for (int i = 0; i < linkedlist.pointer; i++) {
        printf("Entry: ID: %s, Name: %s, DOB: %s, CGPA: %.2lf\n", linkedlist.data[i].entry.id, linkedlist.data[i].entry.name, linkedlist.data[i].entry.dob, linkedlist.data[i].entry.cgpa);
    }
}

void traverseBackward(LINKEDLIST linkedlist) {
    printf("\nTraversal in Forward Direction:\n");
    for (int i = linkedlist.pointer - 1; i >= 0; i--) {
        printf("ID: %s, Name: %s, DOB: %s, CGPA: %.2lf\n", linkedlist.data[i].entry.id, linkedlist.data[i].entry.name, linkedlist.data[i].entry.dob, linkedlist.data[i].entry.cgpa);
    }
}
