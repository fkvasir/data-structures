#include <iostream>
#include <cstdlib>
#include <ctime>

// BST Node
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// BST
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a key into the BST
    void insert(int key) {
        root = insertRecursive(root, key);
    }

    // Search for a key in the BST
    bool search(int key) {
        return searchRecursive(root, key);
    }

    // Delete a key from the BST
    void remove(int key) {
        root = removeRecursive(root, key);
    }

private:
    // Recursive function to insert a key into the BST
    Node* insertRecursive(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }

        return node;
    }

    // Recursive function to search for a key in the BST
    bool searchRecursive(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return searchRecursive(node->left, key);
        } else {
            return searchRecursive(node->right, key);
        }
    }

    // Recursive function to delete a key from the BST
    Node* removeRecursive(Node* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = removeRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = removeRecursive(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMinNode(node->right);
            node->key = temp->key;
            node->right = removeRecursive(node->right, temp->key);
        }

        return node;
    }

    // Helper function to find the minimum node in a BST
    Node* findMinNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
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
    BinarySearchTree bst;

    // Generate a random list of numbers for testing
    const int numElements = 100000000;
    const int minKey = 1;
    const int maxKey = numElements * 10;
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < numElements; ++i) {
        int key = generateRandomNumber(minKey, maxKey);
        bst.insert(key);
    }

    // Measure the runtime of operations
    const int searchKey = generateRandomNumber(minKey, maxKey);

    double insertRuntime = measureRuntime([&bst, minKey, maxKey]() {
        for (int i = 0; i < numElements; ++i) {
            int key = generateRandomNumber(minKey, maxKey);
            bst.insert(key);
        }
    });

    double searchRuntime = measureRuntime([&bst, searchKey]() {
        bst.search(searchKey);
    });

    double deleteRuntime = measureRuntime([&bst, searchKey]() {
        bst.remove(searchKey);
    });

    // Print the runtimes
    std::cout << "Binary Search Tree (BST) Runtimes:" << std::endl;
    std::cout << "Insertion: " << insertRuntime << " seconds" << std::endl;
    std::cout << "Search: " << searchRuntime << " seconds" << std::endl;
    std::cout << "Deletion: " << deleteRuntime << " seconds" << std::endl;

    return 0;
}
