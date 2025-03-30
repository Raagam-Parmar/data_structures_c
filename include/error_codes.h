#ifndef DS_ERROR_CODES_H
#define DS_ERROR_CODES_H

/**
 * @brief Error Codes, general and data structure specific
 * 
 */
typedef enum error_code {
    /* General Error Codes */
    DS_SUCCESS =  0,    /**< Execution Success */
    DS_FAILURE = -1,    /**< Execution Failure */
    DS_MALLOC,          /**< Malloc Failure */
    DS_NULL_ARG,        /**< NULL received as an argument, expected non-NULL */
    DS_NULL_FUNC,       /**< NULL received as an argument for a function pointer, expected non-NULL */

    /* Data Structure Specific Error Codes */
    
    /* Binary Tree */
    BT_PRED_SUCC,       /**<  */

    /* Heap */
    HEAP_ILL_INDEX,     /**< Received illegal heap index (likely out-of-bounds) */

    /* Stack */
    STK_UNDERFLOW,      /**< Attempted POP from an empty stack */

    /* Queue */
    Q_UNDERFLOW,        /**< Attempted DEQUEUE from an empty queue */

    /* Priority Queue */
    PQ_UNDERFLOW,       /**< Attempted DEQUEUE or PEEK from an empty priority queue */

    /* Linked List */

} error_code;

#endif // DS_ERROR_CODES_H
