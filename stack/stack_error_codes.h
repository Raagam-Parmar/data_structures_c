#ifndef STACK_ERROR_CODES
#define STACK_ERROR_CODES

/**
 * @brief Error codes
 * 
 */
typedef enum stack_error_code {
    STACK_NULL_FUNC = -4,   /**< Unexpected NULL passed as a function pointer */
    STACK_UNDERFLOW = -3,   /**< Priority Queue is empty */
    STACK_NULL_ARG  = -2,   /**< Received unexpected NULL as an argument */
    STACK_MALLOC    = -1,   /**< Failure of malloc to allocate memory */
    STACK_SUCCESS   = 0     /**< Successful execution */
} stack_error_code;


#endif // STACK_ERROR_CODES
