#include "include/main.h"

int main() {
    stack_T *stack = init_stack();
    stack_test(stack);
    free(stack);

    puts("\n-------------------------");

    queue_T *queue = init_queue();
    queue_test(queue);
    free(queue);

    return 0;
}


stack_T* init_stack(void) {
    stack_T *stack = (stack_T *)calloc(1, sizeof(stack_T));
    stack->top = NULL;

    return stack;
}

void push(stack_T *stack, void *element) {
    node_T *node = calloc(1, sizeof(node_T));
    node->data = calloc(1, sizeof(element));
    node->data = element;
    node->next = stack->top;
    stack->top = node;
}

void* pop(stack_T *stack) {
    void *element = calloc(1, sizeof(stack->top->data));
    element = stack->top->data;
    stack->top = stack->top->next;
    return element;
}

void display_stack(stack_T *stack) {
    node_T *temp = stack->top;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", *(int *)(temp->data));
        temp = temp->next;
    }
    printf("\n");
}

int stack_is_empty(stack_T *stack) {
    return (stack->top == NULL) ? 1 : 0;
}

void stack_test(stack_T *stack) {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 10; i++) {
        push(stack, &arr[i]);
    }

    display_stack(stack);
    printf(stack_is_empty(stack) ? "Empty\n" : "Not Empty\n");

    printf("Popping the Stack\n");
    for (int i = 0; i < 10; i++) {
        
        int *p = pop(stack);
        printf("Popped %d\n", *p);
    }

    printf(stack_is_empty(stack) ? "Empty\n" : "Not Empty\n");
}

queue_T* init_queue(void) {
    queue_T *queue = calloc(1, sizeof(queue_T));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void enqueue(queue_T *queue, void *element) {
    node_T *node = (node_T *)calloc(1, sizeof(node_T));
    node->data = calloc(1, sizeof(element));
    node->data = element;
    node->next = NULL;
    if (queue->front == NULL) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

void* dequeue(queue_T *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    void *element = calloc(1, sizeof(queue->front->data));
    element = queue->front->data;
    if (queue->rear == queue->front) {
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }
    return element;
}

void display_queue(queue_T *queue) {
    node_T *temp = queue->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", *(int *)(temp->data));
        temp = temp->next;
    }
    printf("\n");
}

int queue_is_empty(queue_T *queue) {
    return (queue->front == NULL);
}

void queue_test(queue_T *queue) {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 10; i++) {
        enqueue(queue, &arr[i]);
    }

    display_queue(queue);
    printf(queue_is_empty(queue) ? "Empty\n" : "Not Empty\n");

    printf("Dequeuing the Queue:\n");
    for (int i = 0; i < 10; i++) {
        
        int *p = dequeue(queue);
        printf("Dequeued %d\n", *p);
    }

    printf(queue_is_empty(queue) ? "Empty\n" : "Not Empty\n");
}
