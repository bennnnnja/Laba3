#include <iostream>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T> *left, *right;
    
    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<class T>
void print_tree(Node<T> *p, int level) {
    if(p == nullptr)
        return;

    print_tree(p->left, level + 1);
    for(int i = 0; i < level; i++)
        cout << ".";
    cout << p->data << endl;
    print_tree(p->right, level + 1);
}

template<class T>
bool find(Node<T>* root, const T& value) {
    if(root == nullptr)
        return false;
    if(root->data == value)
        return true;
    if(value < root->data)
        return find(root->left, value);
    else
        return find(root->right, value);
}

template<class T>
Node<T>* insert(Node<T>* root, const T& value) {
    if(root == nullptr)
        return new Node<T>(value);

    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right, value);

    return root;
}

template<class T>
Node<T>* findMax(Node<T>* node) {
    while(node->right != nullptr)
        node = node->right;
    return node;
}

template<class T>
Node<T>* deleteNode(Node<T>* root, const T& value) {
    if(root == nullptr)
        return root;

    if(value < root->data)
        root->left = deleteNode(root->left, value);
    else if(value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if(root->left == nullptr) {
            Node<T>* temp = root->right;
            delete root;
            return temp;
        } else if(root->right == nullptr) {
            Node<T>* temp = root->left;
            delete root;
            return temp;
        }

        Node<T>* temp = findMax(root->left);
        root->data = temp->data;
        root->left = deleteNode(root->left, temp->data);
    }
    return root;
}

int main() {
    Node<int>* root = nullptr;

    string action;
    int value;

    while(cin >> action) {
        if(action == "ADD") {
            cin >> value;
            if(find(root, value)) {
                cout << "ALREADY" << endl;
            } else {
                root = insert(root, value);
                cout << "DONE" << endl;
            }
        } else if(action == "DELETE") {
            cin >> value;
            if(find(root, value)) {
                root = deleteNode(root, value);
                cout << "DONE" << endl;
            } else {
                cout << "CANNOT" << endl;
            }
        } else if(action == "SEARCH") {
            cin >> value;
            if(find(root, value)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if(action == "PRINTTREE") {
            print_tree(root, 0);
        }
    }

    return 0;
}
