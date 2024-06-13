- Language: C
- The `Member(saying)` method is meant to return a Boolean - true if the saying is in the dictionary, false otherwise.
- The sayings in the collection are in alphabetical order. Predecessor thus gives you the immediately prior saying, and successor the immediately following one.

```
int main(int argc, char* argv[]) {   // Both or whatever

}



---------------------------------------------------------------------------------------------------
struct Saying {                      // Adam -- Header file
    char hawaiianSaying[256];
    char englishTranslation[256];
    char hawaiianExplanation[256];
    char englishExplanation[256];
};
---------------------------------------------------------------------------------------------------



---------------------------------------------------------------------------------------------------
struct Node {                          // Adam -- Header file
    Saying saying;
    char color;  // "Red" and "Black"
    struct Node *left, *right, *parent;
};

struct Node* createNode(struct Saying saying);
void leftRotate(struct Node **root, struct Node *x);
void rightRotate(struct Node **root, struct Node *y);
void insert(struct Node **root, struct Saying saying);
void insertViolationFix(struct Node **root, struct Node *pt);
---------------------------------------------------------------------------------------------------



Node* createNode(Saying saying) {        // My pending code (may have some changes)
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->saying = saying;
    newNode->color = 'R';   // new nodes are red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}




void leftRotate(RBTree *tree, Node *x) {        //Shayde
    // Set y to x's right child
    RBTreeNode *y = x->right;
    
    // Turn y's left subtree into x's right subtree
    x->right = y->left;
    
    // If y's left child is not TNULL, update its parent
    if (y->left != tree->TNULL) {
        y->left->parent = x;
    }
    
    // Update y's parent to x's parent
    y->parent = x->parent;
    
    // If x is the root, make y the new root
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        // If x is a left child, set y as the left child of x's parent
        x->parent->left = y;
    } else {
        // If x is a right child, set y as the right child of x's parent
        x->parent->right = y;
    }
    
    // Make x the left child of y
    y->left = x;
    
    // Update x's parent to y
    x->parent = y;
}


void rightRotate(RBTree *tree, RBTreeNode *x) {        //Shayde
    // Set y to x's left child
    RBTreeNode *y = x->left;
    
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




void insert(Node **root, Saying saying) {    // Adam
    Node *pt = createNode(saying);
    if (*root == NULL)
    {
        pt->color = 'B';
        (*root) = pt;
    }
    else
    {
        Node *y = NULL;
        Node *x = (*root);
        while (x != NULL)
        {
            y = x;
            if (pt->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        pt->parent = y;
        if (pt->key < y->key)
            y->left = pt;
        else
            y->right = pt;
        fixViolation(root, pt);
        }
    }



void insertViolationFix(RBTree *tree, Node *k) {        //Shayde
    RBTreeNode *u; // uncle node

    // Fix the tree until k is the root or the parent of k is black
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle node
            
            if (u->color == RED) { // Case 1: Uncle is red
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) { // Case 2: Node is a left child
                    k = k->parent;
                    rightRotate(tree, k);
                }
                // Case 3: Node is a right child
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(tree, k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle node
            
            if (u->color == RED) { // Case 1: Uncle is red
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) { // Case 2: Node is a right child
                    k = k->parent;
                    leftRotate(tree, k);
                }
                // Case 3: Node is a left child
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(tree, k->parent->parent);
            }
        }
        
        if (k == tree->root) {
            break;
        }
    }
    tree->root->color = BLACK;
}
```
