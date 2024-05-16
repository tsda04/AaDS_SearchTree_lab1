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

    bool insertRecursive(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            return true;
        }
        if (key < node->key) {
            return insertRecursive(node->left, key);
        }
        else if (key > node->key) {
            return insertRecursive(node->right, key);
        }
        return false; // элемент уже существует
    }
    void printRecursive(Node* node) const {
        if (node) {
            printRecursive(node->left);
            std::cout << node->key << " ";
            printRecursive(node->right);
        }
    }
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {
        delete root;
    }
    bool insert(int key) {
        return insertRecursive(root, key);
    }
    void print() const {
        printRecursive(root);
        std::cout << std::endl;
    }
};

int main() {
    BinarySearchTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    tree.print(); // Вывод: 3 5 7
    return 0;
}