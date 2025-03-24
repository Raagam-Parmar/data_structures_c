#ifndef HEAP_ERROR_CODES
#define HEAP_ERROR_CODES

/**
 * @brief Error codes for heap
 * 
 */
typedef enum heap_error_code {
    HEAP_INDEX_ILL = -5,  /**< Index provided to the heap is illegal (out of bounds for the heap) */
    HEAP_NULL_FUNC = -4,  /**< Unexpected NULL passed as a function pointer */
    HEAP_UNDERFLOW = -3,  /**< Priority Queue is empty */
    HEAP_NULL_ARG  = -2,  /**< Received unexpected NULL as an argument */
    HEAP_MALLOC    = -1,  /**< Failure of malloc to allocate memory */
    HEAP_SUCCESS   = 0    /**< Successful execution */
} heap_error_code;

#endif // HEAP_ERROR_CODES
