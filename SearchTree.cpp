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

    bool insertRecursive(Node*& node, int key) { // передача указателя на узел по ссылке
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
        return true; // элемент найден
    }
    void eraseNode(Node*& node) {
        if (!node) {
            return;
        }
        if (!node->left && !node->right) { // узел без дочерних элементов
            delete node;
            node = nullptr;
        }
        else if (!node->left) { // узел с одним правым дочерним элементом
            Node* temp = node;
            node = node->right;
            temp->right = nullptr;
            delete temp;
        }
        else if (!node->right) { // узел с одним левым дочерним элементом
            Node* temp = node;
            node = node->left;
            temp->left = nullptr;
            delete temp;
        }
        else { // узел с двумя дочерними элементами
            Node* minRight = node->right;
            while (minRight->left) {
                minRight = minRight->left;
            }
            node->key = minRight->key;
            eraseNode(minRight);
        }
    }

public:
    int lcg() { //приложение А генератор псевдо-случайных чисел
        static size_t x = 0;
        x = (1021 * x + 24631) % 116640;
        return x;
    }
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
        return false; // элемент не найден
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
    // Конструктор для заполнения дерева случайными числами
    BinarySearchTree(int numRandomValues) : root(nullptr) {
        srand(static_cast<unsigned int>(time(nullptr))); // инициализация генератора случайных чисел
        for (int i = 0; i < numRandomValues; ++i) {
            insert(lcg()); // добавляем случайное число в дерево
        }
    }
    //double measureInsertTime(int numRandomValues)
    //{
    //    clock_t start, end;
    //    double totalTime = 0.0;
    //    for (int i = 0; i < 100; ++i) {
    //        start = clock();
    //        BinarySearchTree tree(numRandomValues);
    //        end = clock();
    //        totalTime += (double)(end - start) / CLOCKS_PER_SEC;
    //    }
    //    return totalTime / 100; // Среднее время заполнения по 100 попыткам
    //}
    //------------------------------------------------------------------------------------
    // Метод для замера времени поиска элемента
    double measureSearchTime(int key) {
        clock_t start, end;
        double totalTime = 0.0;
        for (int i = 0; i < 100; ++i) {
            start = clock();
            contains(key); // Проверяем наличие ключа в дереве
            end = clock();
            totalTime += (double)(end - start) / CLOCKS_PER_SEC;
        }
        return totalTime / 100; // Среднее время поиска по 100 попыткам
    }

    //------------------------------------------------------------------------------------
    // Метод для замера времени вставки элемента
    double measureInsertionTime(int key) {
        clock_t start, end;
        double totalTime = 0.0;
        for (int i = 0; i < 100; ++i) {
            start = clock();
            insertRecursive(root, key);
            end = clock();
            totalTime += (double)(end - start) / CLOCKS_PER_SEC;
            // Удаление вставленного элемента для подготовки к следующей итерации
            erase(key);
        }
        return totalTime / 100; // Среднее время вставки по 100 попыткам
    }
    //------------------------------------------------------------------------------------
    // Метод для замера времени удаления элемента
    double measureDeletionTime(int key) {
        insert(key); // Вставляем ключ перед удалением для обеспечения его наличия
        clock_t start, end;
        double totalTime = 0.0;
        for (int i = 0; i < 100; ++i) {
            start = clock();
            erase(key);
            end = clock();
            totalTime += (double)(end - start) / CLOCKS_PER_SEC;
            // Повторное добавление ключа для следующей итерации
            insert(key);
        }
        return totalTime / 100; // Среднее время удаления по 100 попыткам
    }
};

int main() {
    BinarySearchTree tree;
    int numValues[] = { 1000, 10000, 100000 };
    srand(time(0)); // Инициализация генератора случайных чисел
    for (int i = 0; i < 3; ++i) {
        //double avgTime = tree.measureInsertTime(numValues[i]);
        //std::cout << "Average time to insert " << numValues[i] << " unique random values: " << avgTime << " seconds" << std::endl;
        double avgSearchTime = tree.measureSearchTime(numValues[i]);
        std::cout << "Average time to search for an element in a tree with " << numValues[i] << " unique random values: " << avgSearchTime << " seconds" << std::endl;
    }
    BinarySearchTree tree1000(1000);
    BinarySearchTree tree10000(10000);
    BinarySearchTree tree100000(100000);

    double avgInsertionTime_1000 = tree1000.measureInsertionTime(tree1000.lcg());
    std::cout << "Average insertion time for 1000 unique random values: " << avgInsertionTime_1000 << " seconds" << std::endl;

    double avgDeletionTime_1000 = tree1000.measureDeletionTime(tree1000.lcg());
    std::cout << "Average deletion time for 1000 unique random values: " << avgDeletionTime_1000 << " seconds" << std::endl;

    double avgInsertionTime_10000 = tree10000.measureInsertionTime(tree10000.lcg());
    std::cout << "Average insertion time for 10000 unique random values: " << avgInsertionTime_10000 << " seconds" << std::endl;

    double avgDeletionTime_10000 = tree10000.measureDeletionTime(tree10000.lcg());
    std::cout << "Average deletion time for 10000 unique random values: " << avgDeletionTime_10000 << " seconds" << std::endl;

    double avgInsertionTime_100000 = tree100000.measureInsertionTime(tree100000.lcg());
    std::cout << "Average insertion time for 100000 unique random values: " << avgInsertionTime_100000 << " seconds" << std::endl;

    double avgDeletionTime_100000 = tree100000.measureDeletionTime(tree100000.lcg());
    std::cout << "Average deletion time for 100000 unique random values: " << avgDeletionTime_100000 << " seconds" << std::endl;
  

    //tree.insert(5);
    //tree.insert(3);
    //tree.insert(7);
    //tree.print(); // Вывод: 3 5 7

    //BinarySearchTree tree2(tree); // Вызов конструктора копирования
    //std::cout << "Tree 2 (copy of Tree 1): ";
    //tree2.print(); // Вывод: 3 5 7

    //BinarySearchTree tree3;
    //tree3 = tree; // Вызов оператора присваивания
    //std::cout << "Tree 3 = Tree 1: ";
    //tree2.print(); // Вывод: 3 5 7

    //std::cout << tree.contains(3) << std::endl; // Вывод: 1 (true)
    //std::cout << tree.contains(10) << std::endl; // Вывод: 0 (false)

    //tree.erase(3);
    //tree.print(); // Вывод: 5 7

    //BinarySearchTree treeWithRandomNumbers(10); // Создаем дерево с 10 случайными числами
    //treeWithRandomNumbers.print(); // Выводим содержимое дерева

    
    return 0;
}