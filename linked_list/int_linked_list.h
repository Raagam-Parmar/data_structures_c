#include <stdio.h>
#include <stdlib.h>

#define UNDERFLOW_ERROR_CODE -3
#define NULL_ARG_ERROR_CODE  -2
#define MALLOC_ERROR_CODE    -1
#define SUCCESS_ERROR_CODE    0


// arg-begin
// unit_print
void unit_print(int value) {
    printf("%d", value);
}

// type
typedef int __int;

// compare
int compare(int a, int b) {
    if (a > b)  return 1;
    if (a == b) return 0;
                return -1;
}
// arg-end


typedef struct __int_node {
    __int self;
    struct __int_node *next;
} __int_node;


typedef struct __int_linked_list {
    __int_node *head;
} __int_linked_list;


__int_linked_list * __int_list_create() {
    __int_linked_list *my_list = (__int_linked_list *) malloc(sizeof(__int_linked_list));
    if (! my_list) return NULL;

    my_list -> head = NULL;

    return my_list;
}


size_t __int_list_size(__int_linked_list my_list) {
    size_t size = 0;

    __int_node *traverser = my_list.head;

    while (traverser != NULL) {
        size += 1;
        traverser = traverser -> next;
    }

    return size;
}


int __int_list_append(__int_linked_list *my_list, __int value)
{
    __int_node *new_node = (__int_node *) malloc(sizeof(__int_node));

    if (! new_node) return MALLOC_ERROR_CODE;

    new_node -> self = value;
    new_node -> next = NULL;

    if (my_list -> head == NULL) {
        my_list -> head = new_node;
        return SUCCESS_ERROR_CODE;
    }

    __int_node *traverser = my_list -> head;

    while (traverser -> next != NULL) {
        traverser = traverser -> next;
    }

    traverser -> next = new_node;
    return SUCCESS_ERROR_CODE;
}


int __int_list_print(__int_linked_list my_list) {
    if (my_list.head == NULL) return SUCCESS_ERROR_CODE;

    __int_node *traverser = my_list.head;

    while (traverser != NULL) {
        unit_print(traverser -> self);
        traverser = traverser -> next;
    }
    printf("\n");

    return SUCCESS_ERROR_CODE;
}


int __int_list_destroy(__int_linked_list *my_list) {
    if (! my_list) return SUCCESS_ERROR_CODE;

    while (my_list -> head != NULL) {
        __int_node *trash = my_list -> head;

        my_list -> head = my_list -> head -> next;

        free(trash);
    }

    my_list -> head = NULL;

    return SUCCESS_ERROR_CODE;
}
