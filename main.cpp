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
    Node* a = b->left;
    Node* c = b->right;

    a->right = b;
    b->left = c; 
    updateHeight(b);
    updateHeight(a);
    return a;

}

Node* rotateLeft(Node* a){
    Node* b = a->right;
    Node* c = b->left;

    b->left = a;
    a->right = c; 
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
    
    return balance(root);
    
}

// Utility Functions for AVL Deletion 
Node* findMin(Node* node){
    if (node == nullptr)
    {
        return nullptr;
    }

    // To find the smallest element, we need to traverse
    // to the leftmost subtree
    while (node->left != nullptr)
    {
        node = node->left;
    }
    
    return node;
    
}

Node* removeMin(Node* node){
    if (node->left == nullptr)
    {
        return node->right;
    }
    
    node->left = removeMin(node->left);
    return balance(node);
}

// AVL Deletion 
Node* remove(Node* root, int val){
    // Base Case: If the value is not found 
    if (root == nullptr)
    {
        return nullptr;
    }
    
    // Then we delete as usual by traversing either the 
    // left subtree or right subtree
    if (val < root->val)
    {
        root->left = remove(root->left, val);
    }
    
    else if (val > root->val)
    {
        root->right = remove(root->right, val);
    }

    // The node we want to delete is the current node
    else
    {
        Node* left = root->left;
        Node* right = root->right;
        
        delete root;
        
        // If there is only left child 
        if (right == nullptr)
        {
            return left;
        }
        
        // Otherwise we can replace it with the inorder successor
        // Which is the the minimum in the right subtree
        Node* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;

        return balance(min); // rebalance from the current subtree
    }

    // There may be more than one imbalance after deletion
    // So we can rebalance on the way up
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