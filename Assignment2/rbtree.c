/*****************************************************************
//
//  NAMES:       Adam Graham
//               Shayde Tamura
//
//  ASSIGNMENT:  2
//
//  CLASS:       ICS 311
//
//  INSTRUCTOR:  Brook Conner
//
//  DATE:        June 12, 2024
//
//  FILE:        rbtree.c
//
//  DESCRIPTION:
//   Implementation of red-black tree and dictionary operations.
//
****************************************************************/

#include "rbtree.h"
#include <stdlib.h>
#include <string.h>

/*****************************************************************
//
//  Function name: leftRotate
//
//  DESCRIPTION:
//
//
****************************************************************/

void leftRotate(struct RBTree *tree, struct RBTreeNode *x)
{
    // Set y to x's right child
    struct RBTreeNode *y = x->right;

    // Turn y's left subtree into x's right subtree
    x->right = y->left;

    // If y's left child is not TNULL, update its parent
    if (y->left != tree->TNULL)
    {
        y->left->parent = x;
    }

    // Update y's parent to x's parent
    y->parent = x->parent;

    // If x is the root, make y the new root
    if (x->parent == NULL)
    {
        tree->root = y;
    }
    else if (x == x->parent->left)
    {
        // If x is a left child, set y as the left child of x's parent
        x->parent->left = y;
    }
    else
    {
        // If x is a right child, set y as the right child of x's parent
        x->parent->right = y;
    }
    // Make x the left child of y
    y->left = x;

    // Update x's parent to y
    x->parent = y;
}

/*****************************************************************
//
//  Function name: rightRotate
//
//  DESCRIPTION:
//
//
****************************************************************/

void rightRotate(struct RBTree *tree, struct RBTreeNode *x) {
    // Set y to x's left child
    struct RBTreeNode *y = x->left;

    // Turn y's right subtree into x's left subtree
    x->left = y->right;

    // If y's right child is not TNULL, update its parent
    if (y->right != tree->TNULL) {
        y->right->parent = x;
    }

    // Update y's parent to x's parent
    y->parent = x->parent;

    // If x is the root, make y the new root
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->right) {
        // If x is a right child, set y as the right child of x's parent
        x->parent->right = y;
    } else {
        // If x is a left child, set y as the left child of x's parent
        x->parent->left = y;
    }

    // Make x the right child of y
    y->right = x;

    // Update x's parent to y
    x->parent = y;
}

/*****************************************************************
//
//  Function name: insert
//
//  DESCRIPTION:
//
//
****************************************************************/

void insert(struct RBTree *tree, struct Saying saying) {
    struct RBTreeNode *pt = createNode(saying);
    if (tree->root == NULL)
    {
        pt->color = 'B';
        tree->root = pt;
    }
    else
    {
        struct RBTreeNode *y = NULL;
        struct RBTreeNode *x = tree->root;
        while (x != NULL)
        {
            y = x;
            if (compareSayings(pt->saying, x->saying) < 0)
                x = x->left;
            else
                x = x->right;
        }
        pt->parent = y;
        if (compareSayings(pt->saying, y->saying) < 0)
            y->left = pt;
        else
            y->right = pt;
        insertViolationFix(tree, pt);
    }
}

/*****************************************************************
//
//  Function name: insertViolationFix
//
//  DESCRIPTION:
//
//
****************************************************************/

void insertViolationFix(struct RBTree *tree, struct RBTreeNode *k) {
    struct RBTreeNode *u; // uncle node

    // Fix the tree until k is the root or the parent of k is black
    while (k->parent->color == 'R') {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle node

            if (u->color == 'R') { // Case 1: Uncle is red
                u->color = 'B';
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) { // Case 2: Node is a left child
                    k = k->parent;
                    rightRotate(tree, k);
                }
                // Case 3: Node is a right child
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                leftRotate(tree, k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle node

            if (u->color == 'R') { // Case 1: Uncle is red
                u->color = 'B';
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) { // Case 2: Node is a right child
                    k = k->parent;
                    leftRotate(tree, k);
                }
                // Case 3: Node is a left child
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                rightRotate(tree, k->parent->parent);
            }
        }

        if (k == tree->root) {
            break;
        }
    }
    tree->root->color = 'B';
}

/*****************************************************************
//
//  Function name: createNode
//
//  DESCRIPTION:
//
//
****************************************************************/

struct RBTreeNode* createNode(struct Saying saying) {
    struct RBTreeNode *node = malloc(sizeof(struct RBTreeNode));
    node->saying = saying;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = 'R';  // New nodes are initially red
    return node;
}

/*****************************************************************
//
//  Function name: compareSayings
//
//  DESCRIPTION:
//
//
****************************************************************/

int compareSayings(struct Saying a, struct Saying b) {
    return strcmp(a.hawaiian, b.hawaiian);
}

/*****************************************************************
//
//  Function name: Member
//
//  DESCRIPTION:
//
//
****************************************************************/

int Member(struct RBTree *tree, struct Saying saying) {
    struct RBTreeNode *x = tree->root;
    while (x != NULL)
    {
        int cmp = compareSayings(saying, x->saying);
        if (cmp < 0)
            x = x->left;
        else if (cmp > 0)
            x = x->right;
        else
            return 1;  // Found the saying
    }
    return 0;  // Didn't find the saying
}

/*****************************************************************
//
//  Function name: Predecessor
//
//  DESCRIPTION:
//
//
****************************************************************/

struct Saying Predecessor(struct RBTree *tree, struct Saying saying) {
    struct RBTreeNode *x = tree->root;
    struct RBTreeNode *pred = NULL;
    while (x != NULL)
    {
        int cmp = compareSayings(saying, x->saying);
        if (cmp < 0)
            x = x->left;
        else if (cmp > 0)
        {
            pred = x;
            x = x->right;
        }
        else
        {
            if (x->left != NULL)
            {
                pred = x->left;
                while (pred->right != NULL)
                    pred = pred->right;
            }
            break;
        }
    }
    return pred->saying;
}

/*****************************************************************
//
//  Function name: Successor
//
//  DESCRIPTION:
//
//
****************************************************************/

struct Saying Successor(struct RBTree *tree, struct Saying saying) {
    struct RBTreeNode *x = tree->root;
    struct RBTreeNode *succ = NULL;
    while (x != NULL)
    {
        int cmp = compareSayings(saying, x->saying);
        if (cmp < 0)
        {
            succ = x;
            x = x->left;
        }
        else if (cmp > 0)
            x = x->right;
        else
        {
            if (x->right != NULL)
            {
                succ = x->right;
                while (succ->left != NULL)
                    succ = succ->left;
            }
            break;
        }
    }
    return succ->saying;
}