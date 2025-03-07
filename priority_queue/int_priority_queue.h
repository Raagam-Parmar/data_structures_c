#include <stdio.h>
#include <stdlib.h>


#define NULL_FUNC_ERROR_CODE -4
#define UNDERFLOW_ERROR_CODE -3
#define NULL_ARG_ERROR_CODE  -2
#define MALLOC_ERROR_CODE    -1
#define SUCCESS_ERROR_CODE    0


// arg-begin
typedef int __int;
// arg-end

typedef int  (* compare) (__int, __int);
typedef void (* printer) (__int);
typedef int  (* mprinter) (__int);


typedef struct __int_node { 
    __int               self; 
    struct __int_node * next; 
} __int_node; 


typedef struct __int_pq { 
    __int_node * head;
    size_t       length;
    compare cmp;
    printer prt;
} __int_pq; 


__int_pq * __int_pq_create(compare cmp, printer prt) { 
    if (cmp == NULL || prt == NULL) return NULL;

    __int_pq *queue = (__int_pq *) malloc(sizeof(__int_pq));

    if (! queue) return NULL; 

    queue -> head    = NULL;
    queue -> length  = 0;
    queue -> cmp = cmp;
    queue -> prt = prt;

    return queue; 
} 


int __int_pq_empty(const __int_pq * queue) {
    return (queue -> length == 0);
}


int __int_pq_enq(__int_pq * queue, __int value) { 
    if (queue == NULL) return NULL_ARG_ERROR_CODE; 

    __int_node *new_node = (__int_node *) malloc(sizeof(__int_node)); 

    if (! new_node) return MALLOC_ERROR_CODE; 

    new_node -> self = value; 
    new_node -> next = NULL; 

    if (queue -> head == NULL) { 
        /* head is null */ 
        queue -> head = new_node; 
        queue -> length ++;

        return SUCCESS_ERROR_CODE; 
    } 

    if (queue -> cmp(value, queue -> head -> self) < 0) { 
        /* value < head value */ 
        new_node -> next = queue -> head; 
        queue -> head = new_node; 
        queue -> length ++;

        return SUCCESS_ERROR_CODE; 
    } 

    if (queue -> head -> next == NULL) { 
        /* singleton list */ 
        queue -> head -> next = new_node;
        queue -> length ++;
 
        return SUCCESS_ERROR_CODE; 
    } 

    /* list has at least two elements and we are not inserting at the head */ 
    __int_node *traverser   = queue -> head; 
    __int_node *traverser_n = queue -> head -> next; 
    while (1) { 
        if (traverser_n == NULL) { 
            break; 
        } 

        if (queue -> cmp(value, traverser_n -> self) < 0) { 
            break; 
        } 

        traverser = traverser -> next; 
        traverser_n = traverser_n -> next; 
    } 

    traverser -> next = new_node; 
    new_node -> next = traverser_n; 
    queue -> length ++;

    return SUCCESS_ERROR_CODE; 
} 


int __int_pq_deq(__int_pq *queue, __int *dequeued) { 
    if (queue == NULL)         return NULL_ARG_ERROR_CODE; 
    if (queue -> head == NULL) return UNDERFLOW_ERROR_CODE; 

    *dequeued = queue -> head -> self; 

    __int_node *trash = queue -> head; 
 
    queue -> head = queue -> head -> next; 
    queue -> length --;

    free(trash);

    return SUCCESS_ERROR_CODE; 
} 


int __int_pq_peek(const __int_pq * queue, __int *peek) {
    if (queue == NULL || peek == NULL) return NULL_ARG_ERROR_CODE;
    if (queue -> head == NULL)         return UNDERFLOW_ERROR_CODE;

    *peek = queue -> head -> self;

    return SUCCESS_ERROR_CODE;
}


int __int_pq_map(__int_pq *queue, __int (* map) (__int)) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;
    if (map == NULL)   return NULL_FUNC_ERROR_CODE;

    __int_node *traverser = queue -> head;

    while (traverser != NULL) {
        traverser -> self = map(traverser -> self);

        traverser = traverser -> next;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_pq_mod(__int_pq * queue, void (* modify) (__int *)) {
    if (queue == NULL)  return NULL_ARG_ERROR_CODE;
    if (modify == NULL) return NULL_FUNC_ERROR_CODE;

    __int_node *traverser = queue -> head;

    while (traverser != NULL) {
        modify(& (traverser -> self) );

        traverser = traverser -> next;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_pq_iter(const __int_pq * queue, void (* apply) (__int)) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;
    if (apply == NULL) return NULL_FUNC_ERROR_CODE;

    __int_node *traverser = queue -> head;

    while (traverser != NULL) {
        apply(traverser -> self);

        traverser = traverser -> next;
    }

    return SUCCESS_ERROR_CODE;
}


int __int_pq_print(const __int_pq * queue, printer prt) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;
    if (prt == NULL) prt = queue -> prt;

    __int_pq_iter(queue, prt);
    printf("\n");

    return SUCCESS_ERROR_CODE;
}


int __int_pq_pprint(const __int_pq * queue, printer prt, mprinter mprt, __u_int margin) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;
    if (prt == NULL) prt = queue -> prt;

    int width = 0;
    
    __int_node * traverser = queue -> head;
    while (traverser != NULL) {
        int w = mprt(traverser -> self);
        if (w > width) width = w;

        traverser = traverser -> next;
    }

    printf("+");
    for (__u_int i = 0; i < margin + width + margin; i++) printf("=");
    printf("+\n");
    
    traverser = queue -> head;
    while (traverser != NULL) { 
        prt(traverser -> self); 

        if (traverser -> next != NULL) {
            printf("+");
            for (__u_int i = 0; i < margin + width + margin; i++) printf("-");
            printf("+\n");
        }

        traverser = traverser -> next; 
    }

    printf("+");
    for (__u_int i = 0; i < margin + width + margin; i++) printf("=");
    printf("+\n");

    return SUCCESS_ERROR_CODE; 
}


int __int_pq_free(__int_pq **queue) { 
    if (queue == NULL || *queue == NULL) return NULL_ARG_ERROR_CODE;

    while ((*queue) -> head != NULL) { 
        __int_node *trash = (*queue) -> head; 
        (*queue) -> head = (*queue) -> head -> next; 

        free(trash);
    } 

    free(*queue);

    *queue = NULL;

    return SUCCESS_ERROR_CODE; 
} 
