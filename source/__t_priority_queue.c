#include <stdio.h>
#include <stdlib.h>

#include "include/error_codes.h"

// arg-begin
// Anything inside this will be ignored by the Converter file.

typedef int __t;
// arg-end

/**
 * @brief Compares two objects of the same type, and returns an integer
 * 
 */
typedef int  (* __t_compare) (__t, __t);


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
    __t               self;     /**< The data stored inside the node */
    struct __t_node * next;     /**< A pointer to the next node */
} __t_node; 


/**
 * @brief Stores a list of objects as a linked list, with the highest priority object at the head of the queue.
 * 
 */
typedef struct __t_pq { 
    __t_node *   head;          /**< The highest priority node */
    size_t       length;        /**< The length of the queue */
    __t_compare  cmp;           /**< The compare function used to decide priority */
    __t_printer  prt;           /**< The print function to print objects */
} __t_pq; 


/**
 * @brief Creates an empty priority queue
 * 
 * @param cmp Compare function (non-NULL)
 * @param prt Print function (non-NULL)
 * @return Pointer to a new priority queue, NULL on failure
 */
__t_pq * __t_pq_create(__t_compare cmp, __t_printer prt) { 
    if (cmp == NULL || prt == NULL) return NULL;

    __t_pq *queue = (__t_pq *) malloc(sizeof(__t_pq));

    if (! queue) return NULL; 

    queue -> head    = NULL;
    queue -> length  = 0;
    queue -> cmp     = cmp;
    queue -> prt     = prt;

    return queue; 
} 


/**
 * @brief Checks if a queue is empty
 * 
 * @param queue Queue
 * @return 1 if the queue is empty, 0 otherwise; Error Code
 * @ref error_code
 */
int __t_pq_empty(const __t_pq * queue) {
    if (queue == NULL) return DS_NULL_ARG;
    return (queue -> length == 0);
}


/**
 * @brief Insert a new object inside the priority queue
 * 
 * @param queue Queue
 * @param value New objet to add
 * @return Error Code
 * @ref error_code
 */
int __t_pq_enq(__t_pq * queue, __t value) { 
    if (queue == NULL) return DS_NULL_ARG; 

    __t_node *new_node = (__t_node *) malloc(sizeof(__t_node)); 

    if (! new_node) return DS_MALLOC; 

    new_node -> self = value; 
    new_node -> next = NULL; 

    if (queue -> head == NULL) { 
        queue -> head = new_node; 
        queue -> length ++;

        return DS_SUCCESS; 
    } 

    if (queue -> cmp(value, queue -> head -> self) < 0) { 
        new_node -> next = queue -> head; 
        queue -> head = new_node; 
        queue -> length ++;

        return DS_SUCCESS; 
    } 

    if (queue -> head -> next == NULL) { 
        queue -> head -> next = new_node;
        queue -> length ++;
 
        return DS_SUCCESS; 
    } 

    __t_node *traverser   = queue -> head; 
    __t_node *traverser_n = queue -> head -> next; 
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

    return DS_SUCCESS; 
} 


/**
 * @brief Remove the highest priority object from the queue
 * 
 * @param queue Queue
 * @param dequeued Location to store the removed object
 * @return Error Code
 * @ref error_code
 */
int __t_pq_deq(__t_pq *queue, __t *dequeued) { 
    if (queue == NULL)         return DS_NULL_ARG; 
    if (queue -> head == NULL) return PQ_UNDERFLOW; 

    *dequeued = queue -> head -> self; 

    __t_node *trash = queue -> head; 
 
    queue -> head = queue -> head -> next; 
    queue -> length --;

    free(trash);

    return DS_SUCCESS; 
} 


/**
 * @brief Get the highest priority object from the queue, without removing it
 * 
 * @param queue Queue
 * @param peek Location to store the object
 * @return Error Code
 * @ref error_code
 */
int __t_pq_peek(const __t_pq * queue, __t *peek) {
    if (queue == NULL || peek == NULL) return DS_NULL_ARG;
    if (queue -> head == NULL)         return PQ_UNDERFLOW;

    *peek = queue -> head -> self;

    return DS_SUCCESS;
}


/**
 * @brief Replace every object in the queue with a different object, given by `map`
 * 
 * @param queue Queue
 * @param map Mapping Function
 * @return Error Code
 * @ref error_code
 */
int __t_pq_map(__t_pq *queue, __t (* map) (__t)) {
    if (queue == NULL) return DS_NULL_ARG;
    if (map == NULL)   return DS_NULL_FUNC;

    __t_node *traverser = queue -> head;

    while (traverser != NULL) {
        traverser -> self = map(traverser -> self);

        traverser = traverser -> next;
    }

    return DS_SUCCESS;
}


/**
 * @brief Modify (no replacement) every object in the queue, given by `modify`
 * 
 * @param queue Queue
 * @param modify Modification Function
 * @return Error Code
 * @ref error_code
 */
int __t_pq_mod(__t_pq * queue, void (* modify) (__t *)) {
    if (queue == NULL)  return DS_NULL_ARG;
    if (modify == NULL) return DS_NULL_FUNC;

    __t_node *traverser = queue -> head;

    while (traverser != NULL) {
        modify(& (traverser -> self) );

        traverser = traverser -> next;
    }

    return DS_SUCCESS;
}


/**
 * @brief Iterate through all the objects, using the `apply` function
 * 
 * @param queue Queue
 * @param apply Apply Function
 * @return Error Code
 * @ref error_code
 */
int __t_pq_iter(const __t_pq * queue, void (* apply) (__t)) {
    if (queue == NULL) return DS_NULL_ARG;
    if (apply == NULL) return DS_NULL_FUNC;

    __t_node *traverser = queue -> head;

    while (traverser != NULL) {
        apply(traverser -> self);

        traverser = traverser -> next;
    }

    return DS_SUCCESS;
}


/**
 * @brief Print out the priority queue in order of decreasing priority
 * 
 * @param queue Queue
 * @param prt Optional Print Function (NULL to use the default print function `queue.prt`)
 * @return Error Code
 * @ref error_code
 */
int __t_pq_print(const __t_pq * queue, __t_printer prt) {
    if (queue == NULL) return DS_NULL_ARG;
    if (prt == NULL) prt = queue -> prt;

    __t_pq_iter(queue, prt);
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
int __t_pq_free(__t_pq **queue) { 
    if (queue == NULL || *queue == NULL) return DS_NULL_ARG;

    while ((*queue) -> head != NULL) { 
        __t_node *trash = (*queue) -> head; 
        (*queue) -> head = (*queue) -> head -> next; 

        free(trash);
    } 

    free(*queue);

    *queue = NULL;

    return DS_SUCCESS; 
} 
