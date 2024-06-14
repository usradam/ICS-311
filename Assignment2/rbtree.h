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
//  FILE:        rbtree.h
//
//  DESCRIPTION:
//   Header file for the structure and prototypes of our red-black tree.
//
****************************************************************/

#include "saying.h"

struct RBTreeNode
{
    struct Saying saying;
    struct RBTreeNode *left, *right, *parent;
    char color;  /* 'R' for Red, 'B' for Black */
};

struct RBTree
{
    struct RBTreeNode *root;
    struct RBTreeNode *TNULL;
};

struct RBTreeNode* createNode(struct RBTree *tree, struct Saying saying);
void leftRotate(struct RBTree *tree, struct RBTreeNode *x);
void rightRotate(struct RBTree *tree, struct RBTreeNode *y);
void insert(struct RBTree *tree, struct Saying saying);
void insertViolationFix(struct RBTree *tree, struct RBTreeNode *k);
int compareSayings(struct Saying a, struct Saying b);
int Member(struct RBTree *tree, struct Saying saying);
void inOrderTraversal(struct RBTree *tree, struct RBTreeNode *node);
void MeHua(struct RBTree *tree, struct RBTreeNode *node, wchar_t* word);
void WithWord(struct RBTree *tree, struct RBTreeNode *node, char* word);

