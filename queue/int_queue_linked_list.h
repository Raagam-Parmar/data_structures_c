#include <stdio.h>
#include <stdlib.h>

#define UNDERFLOW_ERROR_CODE -3
#define NULL_ARG_ERROR_CODE  -2
#define MALLOC_ERROR_CODE    -1
#define SUCCESS_ERROR_CODE    0

// arg-begin
void unit_print(int v) {
    printf("%d ", v);
}

typedef int __int;
// arg-end

typedef struct __int_node {
    __int self;
    struct __int_node *next;
} __int_node;


typedef struct __int_queue {
    __int_node *head;
    __int_node *tail;  
} __int_queue;


__int_queue * __int_queue_create() {
    __int_queue *queue = (__int_queue *) malloc(sizeof(__int_queue));
    
    if (! queue) return NULL;

    queue -> head = NULL;
    queue -> tail = NULL;

    return queue;
}


int __int_queue_enqueue(__int_queue *queue, __int value) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __int_node *new_node = (__int_node *) malloc(sizeof(__int_node));

    if (! new_node) return MALLOC_ERROR_CODE;

    new_node -> self = value;
    new_node -> next = NULL;

    if (queue -> head == NULL) {
        queue -> head = new_node;
        queue -> tail = new_node;
    }

    else {
        queue -> head -> next = new_node;
        queue -> head = new_node;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_queue_dequeue(__int_queue *queue, __int *dequeued) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    if (queue -> tail == NULL) return UNDERFLOW_ERROR_CODE;

    __int_node *remove_node = queue -> tail;
    *dequeued = queue -> tail -> self;
    
    queue -> tail = queue -> tail -> next;

    if (queue -> tail == NULL) queue -> head = NULL;

    free(remove_node);

    return SUCCESS_ERROR_CODE;
}


int __int_queue_print(__int_queue queue) {
    if (queue.tail == NULL) return SUCCESS_ERROR_CODE;

    __int_node *traverser = queue.tail;

    while (traverser != NULL) {
        int value = traverser -> self;
        unit_print(value);
        
        traverser = traverser -> next;
    }
    printf("\n");
    
    return SUCCESS_ERROR_CODE;
}


int __int_queue_destroy(__int_queue *queue) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    while (queue -> tail != NULL) {
        __int_node *destroyed_node = queue -> tail;

        queue -> tail = queue -> tail -> next;

        free(destroyed_node);
    }

    queue -> head = NULL;
    queue -> tail = NULL;

    return SUCCESS_ERROR_CODE;
}
