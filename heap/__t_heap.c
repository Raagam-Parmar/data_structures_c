#include <stdio.h>
#include <stdlib.h>

#include "heap_error_codes.h"

// arg-begin
// Anything inside this will be ignored by the Converter file.

typedef int __t;
// arg-end

typedef int (* __t_compare) (__t, __t);


typedef struct __t_heap {
    __t    *     data;
    size_t       capacity;
    size_t       size;
    __t_compare  cmp;
} __t_heap;


__t_heap * __t_heap_create(size_t capacity, __t_compare cmp) {
    __t_heap *heap = (__t_heap *) malloc(sizeof(heap));
    if (heap == NULL) return NULL;

    __t *data = calloc(capacity, sizeof(__t));
    if (data == NULL) return NULL;
    
    heap -> data     = data;
    heap -> capacity = capacity;
    heap -> size     = 0;
    heap -> cmp      = cmp;

    return heap;
}


int __t_parent(int i) {
    return ((i + 1) / 2) - 1;
}

int __t_left(int i) {
    return (2 * i) + 1;
}

int __t_right(int i) {
    return (2 * i) + 2;
}

int __t_first_child_index(__t_heap *heap) {
    int cap = heap -> capacity;
    return (cap + 1) / 2;
}


void __t_swap(__t *array, int i, int j) {
    __t temp = array[i];
    array[i] = array[j];
    array[j] = temp;

    return;
}


int __t_max_heapify(__t_heap *heap, int i) {
    int l = __t_left(i);
    int r = __t_right(i);

    __t *data = heap -> data;
    size_t size = heap -> size;
    __t_compare cmp = heap -> cmp;

    int max_i = i;
    if ((l <= size - 1) && (cmp(data[i], data[l]) < 0)) {
        max_i = l;
    }

    if ((r <= size - 1) && (cmp(data[max_i], data[r]) < 0)) {
        max_i = r;
    }

    if (max_i == i) return HEAP_SUCCESS;

    __t_swap(heap -> data, i, max_i);

    __t_max_heapify(heap, max_i);

    return HEAP_SUCCESS;
}


int __t_build_max_heap(__t_heap *heap) {
    for (int i = __t_first_child_index(heap) - 1; i >= 0; i--) {
        __t_max_heapify(heap, i);
    }

    return HEAP_SUCCESS;
}


int __t_heap_sort(__t_heap *heap) {
    __t_build_max_heap(heap);

    int size = heap -> size;

    for (int i = size - 1; i >= 1; i--) {
        __t_swap(heap -> data, 0, i);
        heap -> size--;
        __t_max_heapify(heap, 0);
    }

    heap -> size = size;

    return HEAP_SUCCESS;
}


int __t_print(const __t_heap *heap) {
    for (int i = 0; i < heap -> size; i++) {
        printf("%d ", heap->data[i]);
    }

    printf("\n");
    return HEAP_SUCCESS;
}
