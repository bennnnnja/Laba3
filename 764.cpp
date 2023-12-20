#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

int height(Node* node) {
    if (node == nullptr)
        return 0;
    
    int left_height = height(node->left);
    int right_height = height(node->right);
    
    return 1 + max(left_height, right_height);
}

bool isBalanced(Node* root) {
    if (root == nullptr)
        return true;

    int left_height = height(root->left);
    int right_height = height(root->right);

    if (abs(left_height - right_height) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return true;

    return false;
}

Node* insert(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

int main() {
    int value;
    cin >> value;
    Node* root = new Node(value);

    while (cin >> value && value != 0) {
        insert(root, value);
    }

    if (isBalanced(root))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
