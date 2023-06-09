#include <iostream>
#include <cstdlib>
#include <ctime>

// AVL Node
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// AVL Tree
class AVL {
public:
    AVL() {
        root = nullptr;
    }

    // Insert a key into the AVL tree
    void insert(int key) {
        root = insertRecursive(root, key);
    }

    // Search for a key in the AVL tree
    bool search(int key) {
        return searchRecursive(root, key);
    }

    // Delete a key from the AVL tree
    void remove(int key) {
        root = removeRecursive(root, key);
    }

private:
    // Get the height of a node
    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Get the balance factor of a node
    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // Rotate a subtree left
    Node* rotateLeft(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + std::max(height(z->left), height(z->right));
        y->height = 1 + std::max(height(y->left), height(y->right));

        return y;
    }

    // Rotate a subtree right
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));

        return x;
    }

    // Create a new node with the given key
    Node* createNode(int key) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    // Insert a key into the AVL tree (recursive helper function)
    Node* insertRecursive(Node* node, int key) {
        if (node == nullptr)
            return createNode(key);

        if (key < node->key)
            node->left = insertRecursive(node->left, key);
        else if (key > node->key)
            node->right = insertRecursive(node->right, key);
        else
            return node; // Duplicate keys are not allowed

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Search for a key in the AVL tree (recursive helper function)
    bool searchRecursive(Node* node, int key) {
        if (node == nullptr)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return searchRecursive(node->left, key);
        else
            return searchRecursive(node->right, key);
    }

    // Find the node with the minimum key in a subtree
    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Delete a key from the AVL tree (recursive helper function)
    Node* removeRecursive(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->key)
            node->left = removeRecursive(node->left, key);
        else if (key > node->key)
            node->right = removeRecursive(node->right, key);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                Node* temp = findMinNode(node->right);
                node->key = temp->key;
                node->right = removeRecursive(node->right, temp->key);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* root;
};

// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to measure runtime of a function
template <typename Func, typename... Args>
double measureRuntime(Func func, Args&&... args) {
    clock_t start = clock();
    func(std::forward<Args>(args)...);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    AVL avlTree;
    // Generate a random list of numbers for testing
    const int numElements = 1000;
    const int minKey = 1;
    const int maxKey = numElements * 10;
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < numElements; ++i) {
        int key = generateRandomNumber(minKey, maxKey);
        avlTree.insert(key);
    }

    // Measure the runtime of operations
    const int searchKey = generateRandomNumber(minKey, maxKey);

    double insertRuntime = measureRuntime([&avlTree, minKey, maxKey]() {
        for (int i = 0; i < numElements; ++i) {
            int key = generateRandomNumber(minKey, maxKey);
            avlTree.insert(key);
        }
    });

    double searchRuntime = measureRuntime([&avlTree, searchKey]() {
        avlTree.search(searchKey);
    });

    double deleteRuntime = measureRuntime([&avlTree, searchKey]() {
        avlTree.remove(searchKey);
    });

    // Print the runtimes
    std::cout << "AVL Tree Runtimes:" << std::endl;
    std::cout << "Insertion: " << insertRuntime << " seconds" << std::endl;
    std::cout << "Search: " << searchRuntime << " seconds" << std::endl;
    std::cout << "Deletion: " << deleteRuntime << " seconds" << std::endl;

    return 0;
}
