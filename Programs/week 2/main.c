#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10

typedef struct Student {
    char id[14];
    char name[50];
    char dob[20];
    double cgpa;
} STUDENT;

typedef struct Queue {
    STUDENT data[CAPACITY];
    int first;
    int last;
} QUEUE;

void enqueue(QUEUE*, STUDENT);
void dequeue(QUEUE*);
void display(QUEUE*);

int main() {
    STUDENT student;
    QUEUE queue;
    queue.first = queue.last = -1;
    FILE *file = fopen("studentin.dat","r");
    while (fscanf(file,"%s %s %s %lf", student.id, student.name, student.dob, &student.cgpa) == 4) {
        enqueue(&queue, student);
    }
    fclose(file);

    display(&queue);

    while(queue.first < (queue.last) % CAPACITY) {
        dequeue(&queue);
    }
}

void enqueue(QUEUE *queue, STUDENT student) {
    if (queue->first == (queue->last + 1) % CAPACITY) {
        printf("Queue Overflow\n");
        return;
    }
    queue->last = (queue->last + 1) % CAPACITY;
    queue->data[queue->last] = student;
}

void dequeue(QUEUE *queue) {
    if (queue->first == -1 && queue->last == -1) {
        printf("Queue Underflow\n");
        return;
    }
    queue->first = (queue->first + 1) % CAPACITY;
    printf("Dequeued Record: ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n" ,queue->data[queue->first].id, queue->data[queue->first].name, queue->data[queue->first].dob, queue->data[queue->first].cgpa);
}

void display(QUEUE *queue) {
    FILE *file = fopen("studentout.dat","w");

    printf("Student Records:\n");
    fprintf(file, "Student Records in FIFO order:\n");
    for (int i = queue->first + 1; i < (queue->last + 1); ++i) {
        printf("ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n",queue->data[i].id, queue->data[i].name, queue->data[i].dob, queue->data[i].cgpa);
        fprintf(file, "ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n",queue->data[i].id, queue->data[i].name, queue->data[i].dob, queue->data[i].cgpa);
    }

    fclose(file);

    printf("Students With CGPA Greater Than 9:\n");

    for (int i = queue->first + 1; i < (queue->last + 1); ++i) {
        if (queue->data[i].cgpa > 9.0) 
        printf("%s\n",queue->data[i].name);
    }
}
