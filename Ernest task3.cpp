#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ==========================================
//Complex ADT - AVL Tree Node
// ==========================================
class Node {
public:
    int itemID;
    string itemName;
    Node* left;
    Node* right;
    int height;
};

// Utility to get the height of the tree
int height(Node* N) {
    if (N == NULL) return 0;
    return N->height;
}

// Utility to create a new node
Node* newNode(int id, string name) {
    Node* node = new Node();
    node->itemID = id;
    node->itemName = name;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right Rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left Rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get Balance factor
int getBalance(Node* N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

// ==========================================
// Error Handling during Insertion
// ==========================================
Node* insert(Node* node, int id, string name) {
    // Error Handling: Prevent negative IDs
    if (id < 0) {
        cout << " [Error] Cannot insert negative Item ID: " << id << endl;
        return node;
    }

    // Standard BST insertion
    if (node == NULL) {
        cout << " [Success] Inserted: " << name << " (ID: " << id << ")" << endl;
        return newNode(id, name);
    }

    if (id < node->itemID)
        node->left = insert(node->left, id, name);
    else if (id > node->itemID)
        node->right = insert(node->right, id, name);
    else {
        // Error Handling: Prevent duplicates
        cout << " [Error] Item ID " << id << " already exists in inventory!" << endl;
        return node;
    }

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance to check if it became unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && id < node->left->itemID)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && id > node->right->itemID)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && id > node->left->itemID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && id < node->right->itemID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Search Function (O(log n) Time Complexity)
void searchItem(Node* root, int id) {
    Node* current = root;
    while (current != NULL) {
        if (current->itemID == id) {
            cout << " --> [Found] Item ID " << id << " is '" << current->itemName << "'" << endl;
            return;
        }
        current = (id < current->itemID) ? current->left : current->right;
    }
    cout << " --> [Not Found] Item ID " << id << " is not in the warehouse." << endl;
}

// ==========================================
// Main Execution File
// ==========================================
int main() {
    Node* root = NULL;
    cout << "--- HIGH-SPEED INVENTORY SYSTEM (AVL TREE) ---" << endl;

    // TODO: Change these inserts for Member 1, Member 2, and Member 3
    root = insert(root, 300, "Engine Oil");
    root = insert(root, 200,  "Break Pads");
    root = insert(root, 400, "Windshield Wipers");
    root = insert(root, -1,  "Corrupted Data"); // Tests error handling
    root = insert(root, 300, "Duplicate Oil"); // Tests duplicate handling

    cout << "\n--- SEARCHING INVENTORY ---" << endl;
    searchItem(root, 400);
    searchItem(root, 777); // Tests missing item

    return 0;
}
