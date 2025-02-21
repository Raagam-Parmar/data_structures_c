#include <stdio.h>
#include <stdlib.h>

#define UNDERFLOW_ERROR_CODE -3
#define NULL_ARG_ERROR_CODE  -2
#define MALLOC_ERROR_CODE    -1
#define SUCCESS_ERROR_CODE    0

// arg-begin
void unit_print(int value) {
    printf("%d", value);
}

typedef int __int;
// arg-end


typedef struct __int_node {
    __int self;
    struct __int_node *next;
} __int_node;


typedef struct __int_stack {
    __int_node *top;
} __int_stack;


__int_stack * __int_stack_create() {
    __int_stack *stack = (__int_stack *) malloc(sizeof(__int_stack));
    if (! stack) return NULL;

    stack -> top = NULL;

    return stack;
}


size_t __int_stack_size(__int_stack stack) {
    if (stack.top == NULL) return 0;

    size_t size = 0;
    __int_node *traverser = stack.top;

    while (traverser != NULL) {
        size += 1;
        traverser = traverser -> next;
    }

    return size;
}


int __int_stack_push(__int_stack *stack, __int value) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    __int_node *new_node = (__int_node *) malloc(sizeof(__int_node));

    if (! new_node) return MALLOC_ERROR_CODE;

    new_node -> self = value;
    new_node -> next = stack -> top;
    stack -> top = new_node;

    return SUCCESS_ERROR_CODE;
}


int __int_stack_pop(__int_stack *stack, __int *popped) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    if (stack -> top == NULL) return UNDERFLOW_ERROR_CODE;

    __int_node *trash = stack -> top;
    *popped = stack -> top -> self;

    stack -> top = stack -> top -> next;

    free(trash);

    return SUCCESS_ERROR_CODE;
}


int __int_stack_print_helper(__int_node *node) {
    if (node == NULL) return SUCCESS_ERROR_CODE;

    __int_stack_print_helper(node -> next);

    unit_print(node -> self);

    return SUCCESS_ERROR_CODE;
}


int __int_stack_print(__int_stack stack) {
    __int_stack_print_helper(stack.top);
    printf("\n");

    return SUCCESS_ERROR_CODE;
}


int __int_stack_destroy(__int_stack *stack) {
    if (stack == NULL) return NULL_ARG_ERROR_CODE;

    while (stack -> top != NULL) {
        __int_node *trash = stack -> top;

        stack -> top = stack -> top -> next;

        free(trash);    
    }

    stack -> top = NULL;

    return SUCCESS_ERROR_CODE;
}
