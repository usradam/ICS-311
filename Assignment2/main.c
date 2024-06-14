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
//   Driver code for the program to test dictionary operations.
//
****************************************************************/

#include "rbtree.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // Set the locale to the user's default locale
    setlocale(LC_ALL, "");

    // Create a new RBTree
    struct RBTree tree;
    tree.TNULL = malloc(sizeof(struct RBTreeNode));
    tree.TNULL->color = 'B';
    tree.TNULL->left = tree.TNULL;
    tree.TNULL->right = tree.TNULL;
    tree.TNULL->parent = tree.TNULL;
    tree.root = tree.TNULL; // Set the tree root to TNULL


    // Hawaiian and English sayings
    struct Saying saying1 = {L"Kūlia i ka nuʻu", "Strive to reach the highest",
                             "Motto of Queen Kapiʻolani", "Strive to do your best."};

    struct Saying saying2 = {L"ʻAʻohe hana i nele i ka uku", "No deed lacks a reward",
                             "Every deed, good or bad, receives its just reward.","Always be kūpono because there are consequences for our actions. Can also be said when karma hits"};

    struct Saying saying3 = {L"ʻAʻohe puʻu kiʻekiʻe ke hoʻāʻo e piʻi", "No cliff is so tall that it cannot be scaled",
                             "No problem is too great when one tries hard to solve it", "Try something even though it seems difficult"};

    struct Saying saying4 = {L"He aliʻi ka ʻāina, he kauā ke kanaka", "The land is a chief; man is its servant",
                             "Land has no need for man, but man needs the land and works it for a livelihood", "We have to take care of the land"};

    struct Saying saying5 = {L"I ka ʻōlelo nō ke ola, i ka ʻōlelo nō ka make", "Life is in speech; death is in speech",
                             "Words can heal; words can destroy", "Be careful with what you say. It can lead to good and bad consequences"};

    // Insert the sayings into the tree
    insert(&tree, saying1);
    insert(&tree, saying2);
    insert(&tree, saying3);
    insert(&tree, saying4);
    insert(&tree, saying5);

    // Call the dictionary operations here and print the results
    wprintf(L"Is 'Kūlia i ka nuʻu' in the tree? %s\n", Member(&tree, saying1) ? L"Yes" : L"No");
    wprintf(L"Is 'ʻAʻohe hana i nele i ka uku' in the tree? %s\n", Member(&tree, saying2) ? L"Yes" : L"No");
    wprintf(L"Is 'ʻAʻohe puʻu kiʻekiʻe ke hoʻāʻo e piʻi' in the tree? %s\n", Member(&tree, saying3) ? L"Yes" : L"No");
    wprintf(L"Is 'He aliʻi ka ʻāina, he kauā ke kanaka' in the tree? %s\n", Member(&tree, saying4) ? L"Yes" : L"No");
    wprintf(L"Is 'I ka ʻōlelo nō ke ola, i ka ʻōlelo nō ka make' in the tree? %s\n", Member(&tree, saying4) ? L"Yes" : L"No");

    printf("\nDictionary List Alphabetized:\n");
    inOrderTraversal(&tree, tree.root);

    // Test the MeHua function
    wprintf(L"\nSayings containing 'nuʻu':\n");
    MeHua(&tree, tree.root, L"nuʻu");

    // Test the WithWord function
    printf("\nSayings containing 'highest':\n");
    WithWord(&tree, tree.root, "highest");

    return 0;
}