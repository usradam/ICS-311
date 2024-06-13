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
//  FILE:        main.c
//
//  DESCRIPTION:
//   Driver code for the program.
//
****************************************************************/

#include "rbtree.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Create a new RBTree
    struct RBTree tree;
    tree.root = NULL;
    tree.TNULL = NULL;

    // Create some sayings
    struct Saying saying1 = {"Aloha", "Hello", "A greeting in Hawaiian", "A greeting in English"};
    struct Saying saying2 = {"Mahalo", "Thank you", "An expression of gratitude in Hawaiian", "An expression of gratitude in English"};

    // Insert the sayings into the tree
    insert(&tree, saying1);
    insert(&tree, saying2);

    // Call your dictionary operations here and print the results
    // For example:
    printf("Is 'Aloha' in the tree? %s\n", Member(&tree, saying1) ? "Yes" : "No");

    return 0;
}