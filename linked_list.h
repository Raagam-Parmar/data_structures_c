#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

#define MALLOC_ERROR_CODE -1

#define MALLOC(type) \
    malloc(sizeof(type))

#define NODE_STRUCT(type) \
    typedef struct node_##type { \
        type self; \
        struct node_##type *next; \
    } node_##type;

#define LIST_STRUCT(type) \
    typedef struct linked_list_##type { \
        struct node_##type *head; \
    } linked_list_##type;

#define LIST_CREATE(type) \
    linked_list_##type * list_create() { \
        linked_list_##type *my_list = MALLOC(linked_list_##type); \
        if (! my_list) return NULL; \
        \
        my_list -> head = NULL; \
        \
        return my_list; \
    }

#define LIST_SIZE(type) \
    size_t list_size(linked_list_##type *my_list) { \
        size_t size = 0; \
        \
        node_##type *traverser = my_list -> head; \
        \
        while (traverser != NULL) { \
            size += 1; \
            traverser = traverser -> next; \
        } \
        \
        return size; \
    }

#define LIST_APPEND(type) \
    int list_append(linked_list_##type *my_list, type value) { \
        node_##type *new_node = MALLOC(node_##type); \
        \
        if (! new_node) return MALLOC_ERROR_CODE; \
        \
        new_node -> self = value; \
        new_node -> next = NULL; \
        \
        if (my_list -> head == NULL) { \
            my_list -> head = new_node; \
            return 0; \
        } \
        \
        node_##type *traverser = my_list -> head; \
        \
        while (traverser -> next != NULL) { \
            traverser = traverser -> next; \
        } \
        \
        traverser -> next = new_node; \
        return 0; \
    }

#define LIST_PRINT(type, print_func) \
    int list_print(linked_list_##type * my_list) { \
        if (my_list -> head == NULL) { \
            return 0; \
        } \
        \
        node_##type *traverser = my_list -> head; \
        \
        while (traverser != NULL) { \
            print_func(traverser -> self); \
            traverser = traverser -> next; \
        } \
        \
        return 0; \
    }

#define LIST_DESTROY(type) \
    int list_destroy(linked_list_##type *my_list) { \
    if (! my_list) return 0; \
    \
        while (my_list -> head != NULL) { \
            node_##type *trash = my_list -> head; \
            \
            my_list -> head = my_list -> head -> next; \
            \
            free(trash); \
        } \
        \
        my_list -> head = NULL; \
        \
        return 0; \
    }

#define GEN_LINKED_LIST(type, print_func) \
NODE_STRUCT(type) \
LIST_STRUCT(type) \
LIST_CREATE(type) \
LIST_APPEND(type) \
LIST_PRINT(type, print_func) \
LIST_DESTROY(type) \
LIST_SIZE(type)

#endif // LINKED_LIST