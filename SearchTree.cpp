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
        Node(const Node& other) : key(other.key), left(nullptr), right(nullptr) {
            if (other.left) {
                left = new Node(*other.left);
            }
            if (other.right) {
                right = new Node(*other.right);
            }
        }

    };
    Node* root;

    bool insertRecursive(Node*& node, int key) { // �������� ��������� �� ���� �� ������
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
        return false; // ������� ��� ����������
    }
    void printRecursive(Node* node) const {
        if (node) {
            printRecursive(node->left);
            std::cout << node->key << " ";
            printRecursive(node->right);
        }
    }
    bool containsRecursive(Node* node, int key) const {
        if (!node) {
            return false;
        }
        if (key < node->key) {
            return containsRecursive(node->left, key);
        }
        else if (key > node->key) {
            return containsRecursive(node->right, key);
        }
        return true; // ������� ������
    }

public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree& other) : root(nullptr) {
        root = new Node(*other.root);
    }
    ~BinarySearchTree() {
        delete root;
    }
    bool insert(int key) {
        return insertRecursive(root, key);
    }
    bool contains(int key) const {
        return containsRecursive(root, key);
    }
    void print() const {
        printRecursive(root);
        std::cout << std::endl;
    }
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            delete root;
            root = new Node(*other.root);
        }
        return *this;
    }

};

int main() {
    BinarySearchTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.print(); // �����: 3 5 7

    BinarySearchTree tree2(tree); // ����� ������������ �����������
    std::cout << "Tree 2 (copy of Tree 1): ";
    tree2.print(); // �����: 3 5 7

    BinarySearchTree tree3;
    tree3 = tree; // ����� ��������� ������������
    std::cout << "Tree 3 = Tree 1: ";
    tree2.print(); // �����: 3 5 7

    std::cout << tree.contains(3) << std::endl; // �����: 1 (true)
    std::cout << tree.contains(10) << std::endl; // �����: 0 (false)

    return 0;
}