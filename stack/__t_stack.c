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
    __t              self;  /**< The object */
    struct __t_node *next;  /**< Pointer to the next node */
} __t_node;


/**
 * @brief Stores objects as a LIFO stack
 * 
 */
typedef struct __t_stk {
    __t_node *top;      /**< The top of the stack */
    size_t    length;   /**< The length of the stack */
    printer   prt;      /**< The print function to print objects */
} __t_stk;


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


__t_stk * __t_stk_create(printer prt) {
    if (prt == NULL) return NULL;

    __t_stk *stack = (__t_stk *) malloc(sizeof(__t_stk));

    if (! stack) return NULL;

    stack -> top    = NULL;
    stack -> length = 0;
    stack -> prt    = prt;

    return stack;
}


/**
 * @brief The size of the stack
 * 
 * @param stack Stack
 * @return The stack size; Error Code
 * @ref error_code
 */
size_t __t_stack_size(const __t_stk * stack) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    return stack -> length;
}


/**
 * @brief Push an object onto the stack
 * 
 * @param stack Stack
 * @param value The object to push
 * @return Error Code
 * @ref error_code
 */
int __t_stk_push(__t_stk *stack, __t value) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    __t_node *new_node = (__t_node *) malloc(sizeof(__t_node));

    if (! new_node) return MALLOC_ERROR_CODE;

    new_node -> self = value;
    new_node -> next = stack -> top;
    stack -> top = new_node;

    return SUCCESS_ERROR_CODE;
}


/**
 * @brief Pop an object from the stack
 * 
 * @param stack Stack
 * @param popped Location to store the popped object
 * @return Error Code
 * @ref error_code
 */
int __t_stk_pop(__t_stk *stack, __t *popped) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    if (stack -> top == NULL) return UNDERFLOW_ERROR_CODE;

    __t_node *trash = stack -> top;
    *popped = stack -> top -> self;

    stack -> top = stack -> top -> next;

    free(trash);

    return SUCCESS_ERROR_CODE;
}


/**
 * @brief A helper function to print all nodes of a stack
 * 
 * @param node Node
 * @return Error Code
 * @ref error_code
 */
int __t_stk_print_helper(__t_node *node) {
    if (node == NULL) return SUCCESS_ERROR_CODE;

    __t_stk_print_helper(node -> next);

    unit_print(node -> self);

    return SUCCESS_ERROR_CODE;
}


/**
 * @brief Print the stack in order of least to most recently added
 * 
 * @param stack Stack
 * @return Error Code
 * @ref error_code
 */
int __t_stk_print(const __t_stk * stack) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    __t_stk_print_helper(stack -> top);
    printf("\n");

    return SUCCESS_ERROR_CODE;
}


/**
 * @brief Free up all the memory allocated for the priority queue
 * @warning Only the memory allocated for the structure will be freed
 * 
 * @param stack Address of a stack pointer
 * @return Error Code
 * @ref error_code
 */
int __t_stk_destroy(__t_stk **stack) {
    if (stack == NULL || *stack == NULL) return NULL_ARG_ERROR_CODE;

    while ((*stack) -> top != NULL) {
        __t_node *trash = (*stack) -> top;

        (*stack) -> top = (*stack) -> top -> next;

        free(trash);    
    }

    free(*stack);

    *stack = NULL;

    return SUCCESS_ERROR_CODE;
}
