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
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*****************************************************************
//
//  Function name: leftRotate
//
//  DESCRIPTION:
//   Performs a left rotation on a given node 'x' to maintain the balance of the tree.
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
//    Performs a right rotation on a given node 'x' to maintain a balanced tree
//
****************************************************************/

void rightRotate(struct RBTree *tree, struct RBTreeNode *x)
{
    // Set y to x's left child
    struct RBTreeNode *y = x->left;

    // Turn y's right subtree into x's left subtree
    x->left = y->right;

    // If y's right child is not TNULL, update its parent
    if (y->right != tree->TNULL)
    {
        y->right->parent = x;
    }

    // Update y's parent to x's parent
    y->parent = x->parent;

    // If x is the root, make y the new root
    if (x->parent == NULL)
    {
        tree->root = y;
    }
    else if (x == x->parent->right)
    {
        // If x is a right child, set y as the right child of x's parent
        x->parent->right = y;
    }
    else
    {
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
//    Creates a new node, then checks if the tree is empty, and finally inserts the node into the tree.
//
****************************************************************/

void insert(struct RBTree *tree, struct Saying saying)
{
    struct RBTreeNode *pt = createNode(tree, saying);  // Pass tree as the first argument
    if (tree->root == tree->TNULL)  // Check for TNULL instead of NULL
    {
        pt->color = 'B';
        tree->root = pt;
    }
    else
    {
        struct RBTreeNode *y = NULL;
        struct RBTreeNode *x = tree->root;
        while (x != tree->TNULL)    // Check for TNULL instead of NULL
        {
            y = x;
            if (compareSayings(pt->saying, x->saying) < 0)
                x = x->left;
            else
                x = x->right;
        }
        pt->parent = y;
        if (y == tree->TNULL)  // Check for TNULL instead of NULL
        {
            tree->root = pt;
        }
        else if (compareSayings(pt->saying, y->saying) < 0)
            y->left = pt;
        else
            y->right = pt;
    }
}


/*****************************************************************
//
//  Function name: insertViolationFix
//
//  DESCRIPTION:
//    Ensures that the red-black tree stays a red-black tree by performing rotations.
//
****************************************************************/

void insertViolationFix(struct RBTree *tree, struct RBTreeNode *k) {
    struct RBTreeNode *u; // uncle node

    // Fix the tree until k is the root or the parent of k is black
    while (k->parent->color == 'R')
    {
        if (k->parent == k->parent->parent->right)
        {
            u = k->parent->parent->left != tree->TNULL ? k->parent->parent->left : tree->TNULL; // uncle node

            if (u->color == 'R')  // Case 1: Uncle is red
            {
                u->color = 'B';
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->left)  // Case 2: Node is a left child
                {
                    k = k->parent;
                    rightRotate(tree, k);
                }
                // Case 3: Node is a right child
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                leftRotate(tree, k->parent->parent);
            }
        }
        else
        {
            u = k->parent->parent->right != tree->TNULL ? k->parent->parent->right : tree->TNULL;

            if (u->color == 'R')    // Case 1: Uncle is red
            {
                u->color = 'B';
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->right)  // Case 2: Node is a right child
                {
                    k = k->parent;
                    leftRotate(tree, k);
                }
                // Case 3: Node is a left child
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                rightRotate(tree, k->parent->parent);
            }
        }
        if (k == tree->root)
        {
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
//    Initializes and creates a new node with a saying, and makes sure it abides by the red-black tree standards.
//
****************************************************************/

struct RBTreeNode* createNode(struct RBTree *tree, struct Saying saying)
{
    struct RBTreeNode *node = malloc(sizeof(struct RBTreeNode));
    node->saying = saying;
    node->left = tree->TNULL;  // Set left child to TNULL
    node->right = tree->TNULL;  // Set right child to TNULL
    node->parent = tree->TNULL;  // Set parent to TNULL
    node->color = 'R';  // New nodes are initially red
    return node;
}

/*****************************************************************
//
//  Function name: compareSayings
//
//  DESCRIPTION:
//    Makes sure that two Hawaiian sayings are compared using locale-aware string collation.
//    
//
****************************************************************/

int compareSayings(struct Saying a, struct Saying b)
{
    setlocale(LC_ALL, "");
    return wcscoll(a.hawaiian, b.hawaiian);
}

/*****************************************************************
//
//  Function name: Member
//
//  DESCRIPTION:
//    Goes throughout the tree to see if a certain saying exists.
//
****************************************************************/

int Member(struct RBTree *tree, struct Saying saying)
{
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
//  Function name: inOrderTraversal
//
//  DESCRIPTION:
//    Traverses the left tree recursively, then prints out the Hawaiian saying, following that traverses the right tree recursively. 
//
****************************************************************/

void inOrderTraversal(struct RBTree *tree, struct RBTreeNode *node)
{
    if (node != tree->TNULL)
    {
        inOrderTraversal(tree, node->left);
        wprintf(L"%ls\n", node->saying.hawaiian);
        inOrderTraversal(tree, node->right);
    }
}

/*****************************************************************
//
//  Function name: MeHua
//
//  DESCRIPTION:
//    Traverses through the red-black tree and prints all of the Hawaiian sayings with a certain Hawaiian word in it. 
//
****************************************************************/

void MeHua(struct RBTree *tree, struct RBTreeNode *node, wchar_t* word) {
    if (node != tree->TNULL) {
        MeHua(tree, node->left, word);
        if (wcsstr(node->saying.hawaiian, word) != NULL) {
            wprintf(L"%ls\n", node->saying.hawaiian);
        }
        MeHua(tree, node->right, word);
    }
}

/*****************************************************************
//
//  Function name: WithWord
//
//  DESCRIPTION:
//    Traverses through the tree and prints all of the English translations with a certain English word in it. 
//
****************************************************************/

void WithWord(struct RBTree *tree, struct RBTreeNode *node, char* word) {
    if (node != tree->TNULL) {
        WithWord(tree, node->left, word);
        if (strstr(node->saying.english, word) != NULL) {
            printf("%s\n", node->saying.english);
        }
        WithWord(tree, node->right, word);
    }
}
