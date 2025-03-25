#ifndef COUNTING_H
#define COUNTING_H

#include <stdlib.h>


int sort_counting(int src[], int dest[], size_t size) {
    int min_i = 0, max_i = 0;

    for (int i = 0; i < size; i++) {
        if (src[i] < src[min_i])
            min_i = i;

        if (src[i] > src[max_i])
            max_i = i;
    }

    int min = src[min_i];
    int max = src[max_i];
    int range = max - min + 1;

    int *cf = (int *) calloc(range, sizeof(int));

    for (int i = 0; i < size; i++)
        cf[src[i] - src[min_i]] ++;

    for (int i = 1; i < range; i++)
        cf[i] += cf[i - 1];
    
    for (int i = size - 1; i >= 0; i--) {
        dest[cf[src[i] - src[min_i]] - 1] = src[i];
        cf[src[i] - src[min_i]] --;
    }

    free(cf);

    return EXIT_SUCCESS;
}

#endif // COUNTING_H