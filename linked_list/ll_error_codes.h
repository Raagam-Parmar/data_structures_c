#ifndef LL_ERROR_CODES
#define LL_ERROR_CODES

/**
 * @brief Error codes
 * 
 */
typedef enum ll_error_code {
    LL_NULL_FUNC = -4,  /**< Unexpected NULL passed as a function pointer */
    LL_UNDERFLOW = -3,  /**< Priority Queue is empty */
    LL_NULL_ARG  = -2,  /**< Received unexpected NULL as an argument */
    LL_MALLOC    = -1,  /**< Failure of malloc to allocate memory */
    LL_SUCCESS   = 0    /**< Successful execution */
} ll_error_code;


#endif // LL_ERROR_CODES
