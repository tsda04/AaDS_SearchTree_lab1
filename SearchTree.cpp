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

    size_t lcg() { //���������� � ��������� ������-��������� �����
        static size_t x = 0;
        x = (1021 * x + 24631) % 116640;
        return x;
    }

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
    void eraseNode(Node*& node) {
        if (!node) {
            return;
        }
        if (!node->left && !node->right) { // ���� ��� �������� ���������
            delete node;
            node = nullptr;
        }
        else if (!node->left) { // ���� � ����� ������ �������� ���������
            Node* temp = node;
            node = node->right;
            temp->right = nullptr;
            delete temp;
        }
        else if (!node->right) { // ���� � ����� ����� �������� ���������
            Node* temp = node;
            node = node->left;
            temp->left = nullptr;
            delete temp;
        }
        else { // ���� � ����� ��������� ����������
            Node* minRight = node->right;
            while (minRight->left) {
                minRight = minRight->left;
            }
            node->key = minRight->key;
            eraseNode(minRight);
        }
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
    bool erase(int key) {
        Node** current = &root;
        while (*current) {
            if (key < (*current)->key) {
                current = &((*current)->left);
            }
            else if (key > (*current)->key) {
                current = &((*current)->right);
            }
            else {
                eraseNode(*current);
                return true;
            }
        }
        return false; // ������� �� ������
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
    // ����������� ��� ���������� ������ ���������� �������
    BinarySearchTree(int numRandomValues) : root(nullptr) {
        srand(static_cast<unsigned int>(time(nullptr))); // ������������� ���������� ��������� �����
        for (int i = 0; i < numRandomValues; ++i) {
            insert(lcg()); // ��������� ��������� ����� � ������
        }
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

    tree.erase(3);
    tree.print(); // �����: 5 7

    BinarySearchTree treeWithRandomNumbers(10); // ������� ������ � 10 ���������� �������
    treeWithRandomNumbers.print(); // ������� ���������� ������

    return 0;
}