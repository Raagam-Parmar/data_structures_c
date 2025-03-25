#ifndef BINARY_TREE_ERROR_CODES
#define BINARY_TREE_ERROR_CODES

/**
 * @brief Error codes for heap
 * 
 */
typedef enum bt_error_code {
    BT_PRED_SUCC = -5,  /**< No predecessor or the successor */
    BT_NULL_FUNC = -4,  /**< Unexpected NULL passed as a function pointer */
    BT_UNDERFLOW = -3,  /**< Priority Queue is empty */
    BT_NULL_ARG  = -2,  /**< Received unexpected NULL as an argument */
    BT_MALLOC    = -1,  /**< Failure of malloc to allocate memory */
    BT_SUCCESS   = 0    /**< Successful execution */
} bt_error_code;

#endif // BINARY_TREE_ERROR_CODES
