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
 * @brief Stores objects as a LIFO stack
 * 
 */
typedef struct __t_stk {
    __t_node *   top;       /**< The top of the stack */
    size_t       length;    /**< The length of the stack */
    __t_printer  prt;       /**< The print function to print objects */
} __t_stk;


/**
 * @brief Creates an empty stack
 * 
 * @param prt Print function (non-NULL)
 * @return Pointer to the new stack; NULL on failure
 */
__t_stk * __t_stk_create(__t_printer prt) {
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
    if (stack == NULL) return DS_NULL_ARG;

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
    if (stack == NULL) return DS_NULL_ARG;

    __t_node *new_node = (__t_node *) malloc(sizeof(__t_node));

    if (! new_node) return DS_MALLOC;

    new_node -> self = value;
    new_node -> next = stack -> top;
    stack -> top = new_node;
    stack -> length ++;

    return DS_SUCCESS;
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
    if (stack == NULL) return DS_NULL_ARG;

    if (stack -> top == NULL) return STK_UNDERFLOW;

    __t_node *trash = stack -> top;
    *popped = stack -> top -> self;

    stack -> top = stack -> top -> next;
    stack -> length --;

    free(trash);

    return DS_SUCCESS;
}


/**
 * @brief A helper function to print all nodes of a stack
 * 
 * @param node Node
 * @return Error Code
 * @ref error_code
 */
int __t_stk_print_helper(__t_node *node, __t_printer prt) {
    if (prt == NULL) return DS_NULL_ARG;

    if (node == NULL) return DS_SUCCESS;

    __t_stk_print_helper(node -> next, prt);

    prt(node -> self);

    return DS_SUCCESS;
}


/**
 * @brief Print the stack in order of least to most recently added
 * 
 * @param stack Stack
 * @param printer Optional Print Function (NULL to use the default print function `stack.prt`)
 * @return Error Code
 * @ref error_code
 */
int __t_stk_print(const __t_stk * stack, __t_printer prt) {
    if (stack == NULL) return DS_NULL_ARG;
    
    if (prt == NULL) prt = stack -> prt;

    __t_stk_print_helper(stack -> top, prt);
    printf("\n");

    return DS_SUCCESS;
}


/**
 * @brief Free up all the memory allocated for the priority queue
 * @warning Only the memory allocated for the structure will be freed
 * 
 * @param stack Address of a stack pointer
 * @return Error Code
 * @ref error_code
 */
int __t_stk_free(__t_stk **stack) {
    if (stack == NULL || *stack == NULL) return DS_NULL_ARG;

    while ((*stack) -> top != NULL) {
        __t_node *trash = (*stack) -> top;

        (*stack) -> top = (*stack) -> top -> next;

        free(trash);    
    }

    free(*stack);

    *stack = NULL;

    return DS_SUCCESS;
}
