#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_STRUCT node_T;

struct NODE_STRUCT {
    void *data;
    node_T *next;
};

typedef struct STACK_STRUCT {
    node_T *top;
} stack_T;

stack_T* init_stack(void);
void push(stack_T *stack, void *element);
void* pop(stack_T *stack);
void display_stack(stack_T *stack);
int stack_is_empty(stack_T *stack);
void stack_test(stack_T *stack);

typedef struct QUEUE_STRUCT {
    node_T *front;
    node_T *rear;
} queue_T;

queue_T* init_queue(void);
void enqueue(queue_T *queue, void *element);
void* dequeue(queue_T *queue);
void display_queue(queue_T *queue);
int queue_is_empty(queue_T *queue);
void queue_test(queue_T *queue);
