#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Defining the binary search / AVL tree structure
struct Node{
    int val;
    int height;
    Node* left;
    Node* right;

    Node(int x) : val(x), height(1), left(nullptr), right(nullptr){}
};

// AVL utility functions
int height(Node* n){
    if (n == nullptr)
    {
        return 0;
    }

    return n->height;
}

void updateHeight(Node* n){
    if (n != nullptr)
    {
        n->height = std::max(height(n->left), height(n->right)) + 1;
    }
}

int getBalance(Node* n){
    if (n == nullptr)
    {
        return 0;
    }

    return height(n->left) - height(n->right);
}

Node* rotateRight(Node* b){
    if (!b || !b->left) return b;  // prevent segfault

    Node* a = b->left;
    b->left = a->right;
    a->right = b;

    updateHeight(b);
    updateHeight(a);
    return a;
}


Node* rotateLeft(Node* a){
    if (!a || !a->right) return a;  // prevent segfault

    Node* b = a->right;
    a->right = b->left;
    b->left = a;

    updateHeight(a);
    updateHeight(b);
    return b;
}

// Balancing is done as per explained in the lectures
Node* balance(Node* node){
    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1)
    {
        if (getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balance < -1)
    {
        if (getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    
    return node;
    
}

// AVL Insertion
// You insert as you would normally in a BST 
// Then we simply balance the tree 
Node* insert(Node* root, int val){
    if (root == nullptr)
    {
        return new Node(val);
    }

    if (val < root->val)
    {
        root->left = insert(root->left, val);
    }
    
    else if (val > root->val)
    {
        root->right = insert(root->right, val);
    }

    else{
        // Skip insertion of duplicates
        return root;
    }
    
    return balance(root);
    
}

// Utility Functions for AVL Deletion 
Node* findMax(Node* node) {
    while (node->right != nullptr)
        node = node->right;
    return node;
}

Node* removeMax(Node* node) {
    if (node->right == nullptr) {
        Node* leftChild = node->left;
        delete node;
        return leftChild;
    }

    node->right = removeMax(node->right);
    return balance(node);
}


// AVL Deletion 
Node* remove(Node* root, int val){
    if (root == nullptr)
        return nullptr;

    if (val < root->val)
        root->left = remove(root->left, val);
    else if (val > root->val)
        root->right = remove(root->right, val);
    else {
        if (root->left == nullptr) {
            Node* rightChild = root->right;
            delete root;
            return rightChild;
        }
        else if (root->right == nullptr) {
            Node* leftChild = root->left;
            delete root;
            return leftChild;
        }
        else {
            Node* maxNode = findMax(root->left);
            root->val = maxNode->val;
            root->left = removeMax(root->left);

        }
    }

    return balance(root);
    
}

// Traversals
void inOrder(Node* root, std::vector<int>& output){
    if (root == nullptr)
    {
        return; 
    }

    inOrder(root->left, output);
    output.push_back(root->val);
    inOrder(root->right, output);
    
}

void postOrder(Node* root, std::vector<int>& output){
    if (root == nullptr)
    {
        return; 
    }

    postOrder(root->left, output);
    postOrder(root->right, output);
    output.push_back(root->val);
}

void preOrder(Node* root, std::vector<int>& output){
    if (root == nullptr)
    {
        return; 
    }

    output.push_back(root->val);
    preOrder(root->left, output);
    preOrder(root->right, output);
}



int main(){
    // Root node for the tree
    Node* root = nullptr;

    // Variables to read in store the operations from the input
    std::string input;
    std::vector<std::string> operations;

    // Looping to read in all operations
    // Loop will break after we reach the final operation (the traversal operation)
    while (std::cin >> input)
    {
        operations.push_back(input);
        if (input == "IN" || input == "POST" || input == "PRE")
        {
            break;
        }
    }

    // Next, we process the insert/delete operations
    for (size_t i = 0; i < operations.size() - 1; i++)
    {
        // Stores the 'A' or 'D'
        char operationType = operations[i][0];

        // Stores the actual integer value to be inserted / removed
        int value = std::stoi(operations[i].substr(1));

        if (operationType == 'A')
        {
            root = insert(root, value);
        }

        else if (operationType == 'D')
        {
            root = remove(root, value);
        }
    }

    // Finally, we need to handle the final traversal operation
    std::string traversal = operations.back();
    std::vector<int> result;

    if (root == nullptr)
    {
        std::cout << "EMPTY \n";
    }

    else
    {
        if (traversal == "IN")
        {
            inOrder(root, result);
        }

        else if (traversal == "POST")
        {
            postOrder(root, result);
        }

        else if (traversal == "PRE")
        {
            preOrder(root, result);
        }
        
        // Print out the tree
        for (size_t i = 0; i < result.size(); i++)
        {
            std::cout << result[i];
            if (i < result.size() - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
    return 0;
}