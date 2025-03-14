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
    __t               self;     /**< The data stored inside the node */
    struct __t_node * next;     /**< A pointer to the next node */
} __t_node; 


/**
 * @brief Stores the objects as a linked list
 * 
 */
typedef struct __t_ll {
    __t_node *head;     /**< The head of the linked list */
    size_t    length;   /**< The length of the linked list */
    printer   prt;      /**< The print function to print objects */
} __t_ll;


/**
 * @brief Error codes
 * 
 */
typedef enum __error_code {
    NULL_FUNC_ERROR_CODE = -4,  /**< Unexpected NULL passed as a function pointer */
    UNDERFLOW_ERROR_CODE = -3,  /**< Priority Queue is empty */
    NULL_ARG_ERROR_CODE  = -2,  /**< Received unexpected NULL as an argument */
    MALLOC_ERROR_CODE    = -1,  /**< Failure of malloc to allocate memory */
    SUCCESS_ERROR_CODE   = 0    /**< Successful execution */
} error_code;


/**
 * @brief Creates an empty linked list
 * 
 * @param prt Print function (non-NULL)
 * @return Pointer to a new linked list, NULL on failure
 */
__t_ll * __t_ll_create(printer prt) {
    if (prt == NULL) return NULL;

    __t_ll *list = (__t_ll *) malloc(sizeof(__t_ll));

    if (! list) return NULL;

    list -> head = NULL;
    list -> length = 0;
    list -> prt = prt;

    return list;
}


/**
 * @brief The length of the linked list
 * 
 * @param list Linked List
 * @return The length of the linked list; Error Code
 * @ref error_code
 */
size_t __t_ll_size(const __t_ll * list) {
    if (list == NULL) return NULL_ARG_ERROR_CODE;
    
    return list -> length;
}


/**
 * @brief Print the Linked List
 * 
 * @param list Linked List
 * @param prt Optional Print Function (NULL to use the default print function `ll.prt`)
 * @return Error Code
 * @ref error_code
 */
int __t_ll_print(const __t_ll * list, printer prt) {
    if (list -> head == NULL) return NULL_ARG_ERROR_CODE;

    if (prt == NULL) prt = list -> prt;

    __t_node *traverser = list -> head;

    while (traverser != NULL) {
        prt(traverser -> self);
        traverser = traverser -> next;
    }
    printf("\n");

    return SUCCESS_ERROR_CODE;
}


/**
 * @brief Free up all the memory allocated for the priority queue
 * @warning Only the memory allocated for the structure will be freed
 * 
 * @param list Location of a linked list pointer
 * @return Error Code
 * @ref error_code
 */
int __t_ll_free(__t_ll **list) {
    if (list == NULL || *list == NULL) return SUCCESS_ERROR_CODE;

    while ((*list) -> head != NULL) {
        __t_node *trash = (*list) -> head;

        (*list) -> head = (*list) -> head -> next;

        free(trash);
    }

    free(*list);

    *list = NULL;

    return SUCCESS_ERROR_CODE;
}
