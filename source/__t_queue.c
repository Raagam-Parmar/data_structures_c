#include <stdio.h>
#include <stdlib.h>

#include "include/error_codes.h"

// arg-begin
// Anything inside this will be ignored by the Converter file.

typedef int __t;
// arg-end

/**
 * @brief Prints the given object
 * 
 */
typedef void (* __t_printer) (__t);


/**
 * @brief Stores the object as a node of a linked list, and the pointer to the next node
 * 
 */
typedef struct __t_node {
    __t              self;  /**< The object */
    struct __t_node *next;  /**< Pointer to the next node */
} __t_node;


/**
 * @brief Stores objects as a FIFO queue
 * 
 */
typedef struct __t_q {
    __t_node *   head;      /**< The head of the queue */
    __t_node *   tail;      /**< The tail of the queue */
    size_t       length;    /**< The length of the queue */
    __t_printer  prt;       /**< The print function to print objects */
} __t_q;


/**
 * @brief Creates an empty linked list
 * 
 * @param prt Print FUnction (non-NULL)
 * @return Pointer to a new linked list, NULL of failure
 */
__t_q * __t_q_create(__t_printer prt) {
    if (prt == NULL) return NULL;

    __t_q *queue = (__t_q *) malloc(sizeof(__t_q));
    
    if (! queue) return NULL;

    queue -> head   = NULL;
    queue -> tail   = NULL;
    queue -> length = 0;
    queue -> prt    = prt;

    return queue;
}


/**
 * @brief Enqueue an object to the given queue
 * 
 * @param queue Queue
 * @param value New object to enqueue
 * @return Error Code
 * @ref error_code
 */
int __t_q_enq(__t_q *queue, __t value) {
    if (queue == NULL) return DS_NULL_ARG;

    __t_node *new_node = (__t_node *) malloc(sizeof(__t_node));

    if (! new_node) return DS_MALLOC;

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

    return DS_SUCCESS;
}


/**
 * @brief Dequeue an object from the given queue
 * 
 * @param queue Queue
 * @param dequeued Location to store the dequeued object
 * @return Error Code
 * @ref error_code
 */
int __t_q_deq(__t_q *queue, __t *dequeued) {
    if (queue == NULL) return DS_NULL_ARG;

    if (queue -> tail == NULL) return Q_UNDERFLOW;

    __t_node *remove_node = queue -> tail;
    *dequeued = queue -> tail -> self;
    
    queue -> tail = queue -> tail -> next;

    if (queue -> tail == NULL) queue -> head = NULL;

    free(remove_node);

    return DS_SUCCESS;
}


/**
 * @brief Print out the queue in the order of addition
 * 
 * @param queue Queue
 * @param Printer Optional Print Function (NULL to use the default print function `queue.prt`)
 * @return Error Code
 * @ref error_code
 */
int __t_q_print(const __t_q *queue, __t_printer prt) {
    if (queue == NULL) return DS_NULL_ARG;
    
    if (prt == NULL) prt = queue -> prt;

    __t_node *traverser = queue -> tail;

    while (traverser != NULL) {
        int value = traverser -> self;
        prt(value);
        
        traverser = traverser -> next;
    }
    printf("\n");
    
    return DS_SUCCESS;
}


/**
 * @brief Free up all the memory allocated for the priority queue
 * @warning Only the memory allocated for the structure will be freed
 * 
 * @param queue Address of a queue pointer
 * @return Error Code
 * @ref error_code
 */
int __t_q_free(__t_q **queue) {
    if (queue == NULL || *queue == NULL) return DS_NULL_ARG;

    while ((*queue) -> tail != NULL) {
        __t_node *trash = (*queue) -> tail;
        (*queue) -> tail = (*queue) -> tail -> next;

        free(trash);
    }

    free(*queue);

    *queue = NULL;

    return DS_SUCCESS;
}
