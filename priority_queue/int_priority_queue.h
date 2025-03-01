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

int unit_compare(int a, int b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}
// arg-end


typedef struct __int_node { 
    __int self; 
    struct __int_node *next; 
} __int_node; 


typedef struct __int_queue { 
    __int_node *head;
    int (* unit_compare) (__int, __int);
} __int_queue; 


__int_queue * __int_queue_create(int (*unit_compare) (__int, __int)) { 
    __int_queue *queue = (__int_queue *) malloc(sizeof(__int_queue)); 

    if (! queue) return NULL; 

    queue -> head = NULL;
    queue -> unit_compare = unit_compare;

    return queue; 
} 


int __int_queue_is_empty(__int_queue queue) {
    if (queue.head == NULL) return 1;
    return 0;
}


int __int_queue_enqueue(__int_queue *queue, __int value) { 
    if (queue == NULL) return NULL_ARG_ERROR_CODE; 

    __int_node *new_node = (__int_node *) malloc(sizeof(__int_node)); 

    if (! new_node) return MALLOC_ERROR_CODE; 

    new_node -> self = value; 
    new_node -> next = NULL; 

    if (queue -> head == NULL) { 
        /* head is null */ 
        queue -> head = new_node; 

        return SUCCESS_ERROR_CODE; 
    } 

    if (queue -> unit_compare(value, queue -> head -> self) < 0) { 
        /* value < head value */ 
        new_node -> next = queue -> head; 
        queue -> head = new_node; 

        return SUCCESS_ERROR_CODE; 
    } 

    if (queue -> head -> next == NULL) { 
        /* singleton list */ 
        queue -> head -> next = new_node; 
 
        return SUCCESS_ERROR_CODE; 
    } 

    /* list has at least two elements and we are not inserting at the head */ 
    __int_node *traverser   = queue -> head; 
    __int_node *traverser_n = queue -> head -> next; 
    while (1) { 
        if (traverser_n == NULL) { 
            break; 
        } 

        if (queue -> unit_compare(value, traverser_n -> self) < 0) { 
            break; 
        } 

        traverser = traverser -> next; 
        traverser_n = traverser_n -> next; 
    } 

    traverser -> next = new_node; 
    new_node -> next = traverser_n; 

    return SUCCESS_ERROR_CODE; 
} 


int __int_queue_dequeue(__int_queue *queue, __int *dequeued) { 
    if (queue == NULL) return NULL_ARG_ERROR_CODE; 

    if (queue -> head == NULL) return UNDERFLOW_ERROR_CODE; 

    *dequeued = queue -> head -> self; 

    __int_node *trash = queue -> head; 
 
    queue -> head = queue -> head -> next; 

    free(trash); 

    return SUCCESS_ERROR_CODE; 
} 


int __int_queue_peek(__int_queue *queue, __int *peek) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    if (queue -> head == NULL) return UNDERFLOW_ERROR_CODE;

    *peek = queue -> head -> self;

    return SUCCESS_ERROR_CODE;
}


int __int_queue_map(__int_queue *queue, __int (* map) (__int)) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __int_node *traverser = queue -> head;

    while (traverser != NULL) {
        traverser -> self = map(traverser -> self);

        traverser = traverser -> next;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_queue_modify(__int_queue *queue, void (* modify) (__int *)) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __int_node *traverser = queue -> head;

    while (traverser != NULL) {
        modify(& (traverser -> self) );

        traverser = traverser -> next;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_queue_iterate(__int_queue *queue, void (* apply) (__int)) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __int_node *traverser = queue -> head;

    while (traverser != NULL) {
        apply(traverser -> self);

        traverser = traverser -> next;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_queue_print(__int_queue queue) {
    __int_queue_iterate(&queue, unit_print);
    printf("\n");

    return  SUCCESS_ERROR_CODE;
}


int __int_queue_pretty_print(__int_queue queue) {
    if (queue.head == NULL) return SUCCESS_ERROR_CODE; 

    __int_node *traverser = queue.head;

    printf("+=======================+\n");

    while (traverser != NULL) { 
        unit_print(traverser -> self); 
        if (traverser -> next != NULL) printf("+-----------------------+\n");

        traverser = traverser -> next; 
    }

    printf("+=======================+\n");
    printf("\n"); 

    return SUCCESS_ERROR_CODE; 
}


int __int_queue_destroy(__int_queue *queue) { 
    if (queue -> head == NULL) return SUCCESS_ERROR_CODE; 

    while (queue -> head != NULL) { 
        __int_node *trash = queue -> head; 

        queue -> head = queue -> head -> next; 

        free(trash); 
    } 

    queue -> head = NULL; 

    return SUCCESS_ERROR_CODE; 
} 
