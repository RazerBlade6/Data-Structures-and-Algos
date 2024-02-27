#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

typedef struct Student {
    char id[14];
    char name[50];
    char dob[15];
    float cgpa;
} STUDENT;

typedef struct Stack {
    STUDENT data[CAPACITY];
    int pointer;
} STACK;

void push(STACK *stack, STUDENT student);
void pop(STACK *stack);
void display(STACK stack);

int main() {
    FILE *file = fopen("studentin.dat", "r");
    if (file == NULL) {
        printf("Error Opening File");
        return 1;
    }

    STACK stack;
    stack.pointer = 0;

    while (fscanf(file, "%s %s %s %f", stack.data[stack.pointer].id, stack.data[stack.pointer].name, stack.data[stack.pointer].dob, &stack.data[stack.pointer].cgpa) == 4) {
        push(&stack, stack.data[stack.pointer]);
    }

    fclose(file);
    
    display(stack);

    while (stack.pointer != -1) {
        pop(&stack);
    }

    return 0;
}

void push(STACK *stack, STUDENT student) {
    if (stack->pointer == CAPACITY - 1) {
        printf("Stack Overflow\n");
    } else {
        stack->data[stack->pointer] = student;
        stack->pointer++;
    }
}

void pop(STACK *stack) {
    printf("Popped Record: ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n", stack->data[stack->pointer].id, stack->data[stack->pointer].name,stack->data[stack->pointer].dob, stack->data[stack->pointer].cgpa);
    stack->pointer--;
}

void display(STACK stack) {
    FILE *file = fopen("studentout.dat", "w");

    if (file == NULL) {
        printf("Error Opening File");
        exit(1);
    }

    printf("\nRecords in Stack:\n");
    fprintf(file, "STUDENT Records in LIFO Order:\n");
    for (int i = stack.pointer; i >= 0; i--) {
        printf("ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n", stack.data[i].id, stack.data[i].name, stack.data[i].dob, stack.data[i].cgpa);
        fprintf(file, "ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n", stack.data[i].id, stack.data[i].name, stack.data[i].dob, stack.data[i].cgpa);
    }
    printf("\n");
}