#include <stdio.h>
#include <stdlib.h>

// arg-begin
// Anything inside this will be ignored by the Converter file.

typedef int __t;
// arg-end

/**
 * @brief Prints the given object
 * 
 */
typedef void (* printer) (__t);


/**
 * @brief Stores the object as a node of a linked list, and the pointer to the next node
 * 
 */
typedef struct __t_node {
    __t              self;
    struct __t_node *next;
} __t_node;


/**
 * @brief Stores a list of objects as a FIFO queue
 * 
 */
typedef struct __t_q {
    __t_node *head;     /**< The head of the queue */
    __t_node *tail;     /**< The tail of the queue */
    size_t   length;    /**< The length of the queue */
    printer  prt;       /**< The print function to print objects */
} __t_q;


/**
 * @brief Error codes
 * 
 */
typedef enum __error_code {
    NULL_FUNC_ERROR_CODE = -4,  /**< Unexpected NULL passed as a function pointer */
    UNDERFLOW_ERROR_CODE = -3,  /**< Queue is empty */
    NULL_ARG_ERROR_CODE  = -2,  /**< Received unexpected NULL as an argument */
    MALLOC_ERROR_CODE    = -1,  /**< Failure of malloc to allocate memory */
    SUCCESS_ERROR_CODE   = 0    /**< Successful execution */
} error_code;


/**
 * @brief Creates an empty linked list
 * 
 * @param prt Print FUnction (non-NULL)
 * @return Pointer to a new linked list, NULL of failure
 */
__t_q * __t_q_create(printer prt) {
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
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __t_node *new_node = (__t_node *) malloc(sizeof(__t_node));

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


/**
 * @brief Dequeue an object from the given queue
 * 
 * @param queue Queue
 * @param dequeued Location to store the dequeued object
 * @return Error Code
 * @ref error_code
 */
int __t_q_deq(__t_q *queue, __t *dequeued) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    if (queue -> tail == NULL) return UNDERFLOW_ERROR_CODE;

    __t_node *remove_node = queue -> tail;
    *dequeued = queue -> tail -> self;
    
    queue -> tail = queue -> tail -> next;

    if (queue -> tail == NULL) queue -> head = NULL;

    free(remove_node);

    return SUCCESS_ERROR_CODE;
}


/**
 * @brief Print  out the queue in the order of addition
 * 
 * @param queue Queue
 * @return Error Code
 * @ref error_code
 */
int __t_q_print(const __t_q *queue) {
    if (queue == NULL) return NULL_ARG_ERROR_CODE;

    __t_node *traverser = queue -> tail;

    while (traverser != NULL) {
        int value = traverser -> self;
        unit_print(value);
        
        traverser = traverser -> next;
    }
    printf("\n");
    
    return SUCCESS_ERROR_CODE;
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
    if (queue == NULL || *queue == NULL) return NULL_ARG_ERROR_CODE;

    while ((*queue) -> tail != NULL) {
        __t_node *trash = (*queue) -> tail;
        (*queue) -> tail = (*queue) -> tail -> next;

        free(trash);
    }

    free(*queue);

    *queue = NULL;

    return SUCCESS_ERROR_CODE;
}
