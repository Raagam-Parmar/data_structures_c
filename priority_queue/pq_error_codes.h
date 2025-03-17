#ifndef PQ_ERROR_CODES
#define PQ_ERROR_CODES

/**
 * @brief Error codes
 * 
 */
typedef enum pq_error_code {
    PQ_NULL_FUNC = -4,  /**< Unexpected NULL passed as a function pointer */
    PQ_UNDERFLOW = -3,  /**< Priority Queue is empty */
    PQ_NULL_ARG  = -2,  /**< Received unexpected NULL as an argument */
    PQ_MALLOC    = -1,  /**< Failure of malloc to allocate memory */
    PQ_SUCCESS   = 0    /**< Successful execution */
} pq_error_code;


#endif // PQ_ERROR_CODES
