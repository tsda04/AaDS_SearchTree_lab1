#include <iostream>

class BinarySearchTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int key) : key(key), left(nullptr), right(nullptr) {}
        ~Node() {
            delete left;
            delete right;
        }
    };
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {
        delete root;
    }
};

int main() {
    return 0;
}