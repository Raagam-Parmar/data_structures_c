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
    __int_node *entry;
} __int_queue;


__int_queue * __int_queue_create() {
    __int_queue *queue = (__int_queue *) malloc(sizeof(__int_queue));

    if (! queue) return NULL;

    queue -> entry = NULL;

    return queue;
}


int __int_queue_enqueue(__int_queue *queue, __int value) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __int_node *new_node = (__int_node *) malloc(sizeof(__int_node));

    if (! new_node) return MALLOC_ERROR_CODE;

    new_node -> self = value;
    new_node -> next = NULL;

    if (queue -> entry == NULL) {
        new_node -> next = new_node;
        queue -> entry = new_node;

        return SUCCESS_ERROR_CODE;
    }

    new_node -> self = queue -> entry -> self;
    new_node -> next = queue -> entry -> next;

    queue -> entry -> self = value;
    queue -> entry -> next = new_node;

    queue -> entry = new_node;

    return SUCCESS_ERROR_CODE;
}


int __int_queue_dequeue(__int_queue *queue, __int *dequeued) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    if (queue -> entry == NULL) return UNDERFLOW_ERROR_CODE;

    if (queue -> entry -> next == queue -> entry) {
        __int_node *trash = queue -> entry;

        *dequeued = queue -> entry -> self;

        queue -> entry = NULL;

        free(trash);

        return SUCCESS_ERROR_CODE;
    }

    __int_node *trash = queue -> entry -> next;

    *dequeued = queue -> entry -> self;

    queue -> entry -> self = queue -> entry -> next -> self;
    queue -> entry -> next = queue -> entry -> next -> next;

    free(trash);
    
    return SUCCESS_ERROR_CODE;
}


int __int_queue_print(__int_queue queue) {
    if (queue.entry == NULL) return SUCCESS_ERROR_CODE;

    if (queue.entry -> next == queue.entry) {
        unit_print(queue.entry -> self);
        printf("\n");

        return SUCCESS_ERROR_CODE;
    }

    __int_node *traverser = queue.entry;
    
    unit_print(traverser -> self);
    traverser = traverser -> next;

    while (traverser != queue.entry) {
        unit_print(traverser -> self);
        traverser = traverser -> next;
    }
    printf("\n");

    return SUCCESS_ERROR_CODE;
}


int __int_queue_destroy(__int_queue *queue) {
    if (queue -> entry == NULL) return SUCCESS_ERROR_CODE;

    __int_node *traverser = queue -> entry;

    while (traverser -> next != queue -> entry) {
        __int_node *trash = traverser;
        traverser = traverser -> next;

        free(trash);
    }

    free(traverser);

    queue -> entry = NULL;

    return SUCCESS_ERROR_CODE;
}
