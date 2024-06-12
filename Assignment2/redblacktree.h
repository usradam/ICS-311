/*****************************************************************
//
//  NAME:        Adam Graham
//
//  Assignment:  2
//
//  CLASS:       ICS 311
//
//  INSTRUCTOR:  Brook Conner
//
//  DATE:        June 12, 2024
//
//  FILE:        redblacktree.h
//
//  DESCRIPTION:
//   Header file for the structure of a red-black tree.
//
****************************************************************/

#include "saying.h"

struct Node
{
    struct Saying saying;
    struct Node *left, *right, *parent;
    char color;  /* 'R' for Red, 'B' for Black */
};

struct Node* createNode(struct Saying saying);
void leftRotate(struct Node **root, struct Node *x);
void rightRotate(struct Node **root, struct Node *y);
void insert(struct Node **root, struct Saying saying);
void insertViolationFix(struct Node **root, struct Node *pt);