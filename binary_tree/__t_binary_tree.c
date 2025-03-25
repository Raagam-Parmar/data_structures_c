#include <stdio.h>
#include <stdlib.h>

#include "binary_tree_error_codes.h"

// arg-begin
// Anything inside this will be ignored by the Converter file.

typedef int __t;
// arg-end

typedef int (* __t_compare) (__t, __t);


typedef void (* __t_printer) (__t);


typedef int (* __t_m_printer) (__t);


typedef struct __t_node {
    __t                 value;
    struct __t_node *   left;
    struct __t_node *   right;
} __t_node;


typedef struct __t_btree {
    __t_node *      root;
    size_t          height;
    __t_compare     cmp;
    __t_printer     prt;
    __t_m_printer   mprt;
} __t_btree;


typedef enum print_type {
    TREE,
    PREFIX,
    POSTFIX,
    INFIX
} print_type;


__t_btree * __t_btree_create(__t_compare cmp, __t_printer prt, __t_m_printer mprt) {
    __t_btree *bt = (__t_btree *) malloc(sizeof(__t_btree));
    if (bt == NULL) return NULL;

    bt -> root   = NULL;
    bt -> height = 0;
    bt -> cmp    = cmp;
    bt -> prt    = prt;
    bt -> mprt   = mprt;

    return bt;
}


int __t_btree_insert(__t_btree *bt, __t value) {
    if (bt == NULL) return BT_NULL_ARG;

    if (bt -> root == NULL) {
        __t_node *new = (__t_node *) malloc(sizeof(__t_node));
        if (new == NULL) return BT_MALLOC;

        new -> value = value;
        new -> left = NULL;
        new -> right = NULL;

        bt -> root = new;
        return bt;
    }

    __t_node *traverser = bt -> root;

    while (1) {
        if (value == traverser -> value) return BT_SUCCESS;

        if (value < traverser -> value) {
            if (traverser -> left != NULL) {
                traverser = traverser -> left;
                continue;
            }

            __t_node *new = (__t_node *) malloc(sizeof(__t_node));
            if (new == NULL) return BT_MALLOC;

            new -> value = value;
            new -> left = NULL;
            new -> right = NULL;

            traverser -> left = new;

            return BT_SUCCESS;
        }

        if (value > traverser -> value) {
            if (traverser -> right != NULL) {
                traverser = traverser -> right;
                continue;
            }

            __t_node *new = (__t_node *) malloc(sizeof(__t_node));
            if (new == NULL) return BT_MALLOC;

            new -> value = value;
            new -> left = NULL;
            new -> right = NULL;

            traverser -> right = new;

            return BT_SUCCESS;
        }
    }

    return BT_SUCCESS;
}


void __t_btree_infix_helper(__t_node *node, __t_printer prt) {
    if (node == NULL) return;

    __t_btree_infix_helper(node -> left, prt);
    prt(node -> value);
    __t_btree_infix_helper(node -> right, prt);

    return;    
}


void __t_btree_prefix_helper(__t_node *node, __t_printer prt) {
    if (node == NULL) return;

    prt(node -> value);
    __t_btree_prefix_helper(node -> left, prt);
    __t_btree_prefix_helper(node -> right, prt);

    return;    
}


void __t_btree_postfix_helper(__t_node *node, __t_printer prt) {
    if (node == NULL) return;

    __t_btree_postfix_helper(node -> left, prt);
    __t_btree_postfix_helper(node -> right, prt);
    prt(node -> value);

    return;    
}


int __t_btree_infix(__t_btree *bt, __t_printer prt) {
    if (bt == NULL) return BT_NULL_ARG;
    if (prt == NULL) prt = bt -> prt;

    __t_btree_infix_helper(bt -> root, prt);
    printf("\n");

    return BT_SUCCESS;
}


int __t_btree_prefix(__t_btree *bt, __t_printer prt) {
    if (bt == NULL) return BT_NULL_ARG;
    if (prt == NULL) prt = bt -> prt;

    __t_btree_prefix_helper(bt -> root, prt);
    printf("\n");

    return BT_SUCCESS;
}


int __t_btree_postfix(__t_btree *bt, __t_printer prt) {
    if (bt == NULL) return BT_NULL_ARG;
    if (prt == NULL) prt = bt -> prt;

    __t_btree_postfix_helper(bt -> root, prt);
    printf("\n");

    return BT_SUCCESS;
}


int __t_btree_height(__t_node *node) {
    if (node == NULL) return 0;

    int height_left = __t_btree_height(node -> left);
    int height_right = __t_btree_height(node -> right);

    int height_max = height_left > height_right ? height_left : height_right;

    return height_max + 1;
}

int __t_btree_min(__t_btree *bt, __t *min) {
    if (bt == NULL) return BT_NULL_ARG;

    __t_node *traverser = bt -> root;
    while (1) {
        if (traverser -> left == NULL) {
            *min = traverser -> value;
            break;
        }

        traverser = traverser -> left;
    }

    return BT_SUCCESS;
}


int __t_btree_min_helper(__t_node *node, __t *min) {
    __t_node *traverser = node;
    while (1) {
        if (traverser -> left == NULL) {
            *min = traverser -> value;
            break;
        }

        traverser = traverser -> left;
    }

    return BT_SUCCESS;
}



int __t_btree_max(__t_btree *bt, __t *min) {
    if (bt == NULL) return BT_NULL_ARG;

    __t_node *traverser = bt -> root;
    while (1) {
        if (traverser -> right == NULL) {
            *min = traverser -> value;
            break;
        }

        traverser = traverser -> right;
    }

    return BT_SUCCESS;
}

int __t_btree_max_helper(__t_node *node, __t *min) {
    __t_node *traverser = node;
    while (1) {
        if (traverser -> right == NULL) {
            *min = traverser -> value;
            break;
        }

        traverser = traverser -> right;
    }

    return BT_SUCCESS;
}


int __t_btree_pred_helper(__t_node *node, __t value, __t *pred) {
    if (node == NULL) return BT_PRED_SUCC;

    if (value == node -> value) {
        __t left_max;
        int ec = __t_btree_max_helper(node -> left, &left_max);
        
        if (ec == BT_NULL_ARG)
            return BT_PRED_SUCC;
        
        *pred = left_max;
        return BT_SUCCESS;
    }

    if (value < node -> value) {
        return __t_btree_pred_helper(node -> left, value, pred);
    }

    if (value > node -> value) {
        int ec = __t_btree_pred_helper(node -> right, value, pred);
        if (ec == BT_PRED_SUCC) {
            *pred = node -> value;
        }

        return BT_SUCCESS;
    }
}


int __t_btree_pred(__t_btree *bt, __t value, __t *pred) {
    if (bt == NULL) return BT_NULL_ARG;
}