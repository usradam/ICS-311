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
#include <locale.h>

int main(int argc, char* argv[]) {
    // Set the locale to the user's default locale
    setlocale(LC_ALL, "");

    // Create a new RBTree
    struct RBTree tree;
    tree.root = NULL;
    tree.TNULL = NULL;

    // Create some sayings
    // TEMPLATE SAYINGS - Note reflective of real things
    struct Saying saying1 = {L"E kaupē aku nō i ka hoe a kō mai", L"Hello", L"A greeting in Hawaiian", L"A greeting in English"};
    struct Saying saying2 = {L"Mahalo", L"Thank you", L"An expression of gratitude in Hawaiian", L"An expression of gratitude in English"};
    struct Saying saying3 = {L"Amount", L"Thank you", L"An expression of gratitude in Hawaiian", L"An expression of gratitude in English"};
    struct Saying saying4 = {L"Cool", L"Thank you", L"An expression of gratitude in Hawaiian", L"An expression of gratitude in English"};
    struct Saying saying5 = {L"Ua hala ʻē ka Puʻulena.", L"The Puʻulena wind of Puna has passed.", L"An expression of gratitude in Hawaiian", L"Too late! Your chance has passed. Be quick next time."};


    // Insert the sayings into the tree
    insert(&tree, saying1);
    insert(&tree, saying2);
    insert(&tree, saying3);
    insert(&tree, saying4);
    insert(&tree, saying5);

    // Call your dictionary operations here and print the results
    // For example:
    wprintf(L"Is 'E kaupē aku nō i ka hoe a kō mai' in the tree? %s\n", Member(&tree, saying1) ? L"Yes" : L"No");

    printf("\nAlphabetized Dictionary List:\n");
    inOrderTraversal(&tree, tree.root);

    return 0;
}