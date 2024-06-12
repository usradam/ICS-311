```
int main(int argc, char* argv[]) {   // Both or whatever

}


struct Saying {                      // Adam --  Will be a header file
    char hawaiianSaying[256];
    char englishTranslation[256];
    char hawaiianExplanation[256];
    char englishExplanation[256];
};



struct Node {                          // Adam -- Will be a header file
    Saying saying;
    char color;  // "Red" and "Black"
    struct Node *left, *right, *parent;
};

Node* createNode(Saying saying) {
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
