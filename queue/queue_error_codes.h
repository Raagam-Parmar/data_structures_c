#ifndef QUEUE_ERROR_CODES
#define QUEUE_ERROR_CODES

/**
 * @brief Error codes for queue
 * 
 */
typedef enum queue_error_code {
    QUEUE_NULL_FUNC = -4,  /**< Unexpected NULL passed as a function pointer */
    QUEUE_UNDERFLOW = -3,  /**< Priority Queue is empty */
    QUEUE_NULL_ARG  = -2,  /**< Received unexpected NULL as an argument */
    QUEUE_MALLOC    = -1,  /**< Failure of malloc to allocate memory */
    QUEUE_SUCCESS   = 0    /**< Successful execution */
} queue_error_code;


#endif // QUEUE_ERROR_CODES
