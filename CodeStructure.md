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




void rotateLeft() {  // Shayde

}



void rotateRight() {    // Shayde

}




void insert() {    // Adam  

}




void insertViolationFix() {   // Shayde

}
```
