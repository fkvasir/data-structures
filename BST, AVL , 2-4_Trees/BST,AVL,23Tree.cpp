#include <iostream>
#include <chrono>

// Binary Search Tree (BST) Node
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

// AVL Tree Node
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// (2,4) Tree Node
struct TwoFourNode {
    int keys[3];
    TwoFourNode* children[4];
    int keyCount;
};

// Binary Search Tree (BST)
class BST {
private:
    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, int data) {
        if (node == nullptr) {
            node = new BSTNode;
            node->data = data;
            node->left = node->right = nullptr;
        } else if (data <= node->data) {
            node->left = insertRecursive(node->left, data);
        } else {
            node->right = insertRecursive(node->right, data);
        }
        return node;
    }

    bool searchRecursive(BSTNode* node, int data) {
        if (node == nullptr) {
            return false;
        } else if (data == node->data) {
            return true;
        } else if (data < node->data) {
            return searchRecursive(node->left, data);
        } else {
            return searchRecursive(node->right, data);
        }
    }

    BSTNode* deleteRecursive(BSTNode* node, int data) {
        if (node == nullptr) {
            return nullptr;
        } else if (data < node->data) {
            node->left = deleteRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = deleteRecursive(node->right, data);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                BSTNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node;
                node = node->left;
                delete temp;
            } else {
                BSTNode* successor = findMinimum(node->right);
                node->data = successor->data;
                node->right = deleteRecursive(node->right, successor->data);
            }
        }
        return node;
    }

    BSTNode* findMinimum(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    bool search(int data) {
        return searchRecursive(root, data);
    }

    void remove(int data) {
        root = deleteRecursive(root, data);
    }
};

// AVL Tree
class AVL {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        if (node == nullptr) {
            return -1;
        } else {
            return node->height;
        }
    }

    int getBalance(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return height(node->left) - height(node->right);
        }
    }

    AVLNode* rotateRight(AVLNode* node) {
        AVLNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        node->height = 1 + std::max(height(node->left), height(node->right));
        newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));
        return newRoot;
    }

    AVLNode* rotateLeft(AVLNode* node) {
        AVLNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        node->height = 1 + std::max(height(node->left), height(node->right));
        newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));
        return newRoot;
    }

    AVLNode* insertRecursive(AVLNode* node, int data) {
        if (node == nullptr) {
            node = new AVLNode;
            node->data = data;
            node->left = node->right = nullptr;
            node->height = 0;
        } else if (data <= node->data) {
            node->left = insertRecursive(node->left, data);
        } else {
            node->right = insertRecursive(node->right, data);
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data) {
            return rotateRight(node);
        }

        if (balance < -1 && data > node->right->data) {
            return rotateLeft(node);
        }

        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    bool searchRecursive(AVLNode* node, int data) {
        if (node == nullptr) {
            return false;
        } else if (data == node->data) {
            return true;
        } else if (data < node->data) {
            return searchRecursive(node->left, data);
        } else {
            return searchRecursive(node->right, data);
        }
    }

    AVLNode* deleteRecursive(AVLNode* node, int data) {
        if (node == nullptr) {
            return nullptr;
        } else if (data < node->data) {
            node->left = deleteRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = deleteRecursive(node->right, data);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                AVLNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                AVLNode* temp = node;
                node = node->left;
                delete temp;
            } else {
                AVLNode* successor = findMinimum(node->right);
                node->data = successor->data;
                node->right = deleteRecursive(node->right, successor->data);
            }
        }

        if (node == nullptr) {
            return nullptr;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* findMinimum(AVLNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    AVL() {
        root = nullptr;
    }

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    bool search(int data) {
        return searchRecursive(root, data);
    }

    void remove(int data) {
        root = deleteRecursive(root, data);
    }
};

// (2,4) Tree
class TwoFourTree {
private:
    TwoFourNode* root;

    TwoFourNode* createNode(int data) {
        TwoFourNode* node = new TwoFourNode;
        node->keys[0] = data;
        node->keyCount = 1;
        for (int i = 0; i < 4; i++) {
            node->children[i] = nullptr;
        }
        return node;
    }

    void splitChild(TwoFourNode* parent, int index) {
        TwoFourNode* child = parent->children[index];
        TwoFourNode* newNode = createNode(child->keys[1]);

        parent->keys[parent->keyCount] = child->keys[0];
        parent->keyCount++;

        for (int i = parent->keyCount - 1; i > index; i--) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[index + 1] = newNode;

        for (int i = parent->keyCount - 2; i >= index; i--) {
            parent->keys[i + 1] = parent->keys[i];
        }
        parent->keys[index] = child->keys[1];

        child->keys[0] = child->keys[2];
        child->keyCount = 1;
        parent->children[index]->keyCount = 1;
    }

    TwoFourNode* insertRecursive(TwoFourNode* node, int data) {
        if (node == nullptr) {
            return createNode(data);
        }

        if (node->keyCount == 1) {
            if (data < node->keys[0]) {
                node->keys[1] = node->keys[0];
                node->keys[0] = data;
            } else {
                node->keys[1] = data;
            }
            node->keyCount = 2;
            return node;
        }

        if (data < node->keys[0]) {
            node->children[0] = insertRecursive(node->children[0], data);
        } else if (data > node->keys[1]) {
            node->children[2] = insertRecursive(node->children[2], data);
        } else {
            node->children[1] = insertRecursive(node->children[1], data);
        }

        if (node->children[1] != nullptr) {
            splitChild(node, 1);
        }

        return node;
    }

    bool searchRecursive(TwoFourNode* node, int data) {
        if (node == nullptr) {
            return false;
        } else if (data == node->keys[0] || data == node->keys[1]) {
            return true;
        } else if (data < node->keys[0]) {
            return searchRecursive(node->children[0], data);
        } else if (node->keyCount == 2 && data > node->keys[1]) {
            return searchRecursive(node->children[2], data);
        } else {
            return searchRecursive(node->children[1], data);
        }
    }

    TwoFourNode* deleteRecursive(TwoFourNode* node, int data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->keyCount == 1) {
            if (data == node->keys[0]) {
                delete node;
                return nullptr;
            } else {
                return node;
            }
        }

        if (data < node->keys[0]) {
            node->children[0] = deleteRecursive(node->children[0], data);
        } else if (data > node->keys[1]) {
            node->children[2] = deleteRecursive(node->children[2], data);
        } else {
            node->children[1] = deleteRecursive(node->children[1], data);
        }

        if (node->children[1] == nullptr) {
            if (data == node->keys[0]) {
                node->keys[0] = node->keys[1];
                node->keyCount = 1;
                node->children[1] = node->children[2];
                node->children[2] = nullptr;
            }
        }

        return node;
    }

public:
    TwoFourTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    bool search(int data) {
        return searchRecursive(root, data);
    }

    void remove(int data) {
        root = deleteRecursive(root, data);
    }
};

template<typename Func>
long long measureRuntime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {

    // Measure runtime of insert operation
    long long bstInsertTime = measureRuntime([&]() {
        // Perform insert operation on BST
    });

    long long avlInsertTime = measureRuntime([&]() {
        // Perform insert operation on AVL tree
    });

    long long twoFourInsertTime = measureRuntime([&]() {
        // Perform insert operation on (2,4) tree
    });

    // Measure runtime of search operation
    long long bstSearchTime = measureRuntime([&]() {
        // Perform search operation on BST
    });

    long long avlSearchTime = measureRuntime([&]() {
        // Perform search operation on AVL tree
    });

    long long twoFourSearchTime = measureRuntime([&]() {
        // Perform search operation on (2,4) tree
    });

    // Measure runtime of delete operation
    long long bstDeleteTime = measureRuntime([&]() {
        // Perform delete operation on BST
    });

    long long avlDeleteTime = measureRuntime([&]() {
        // Perform delete operation on AVL tree
    });

    long long twoFourDeleteTime = measureRuntime([&]() {
        // Perform delete operation on (2,4) tree
    });

    // Print the runtime of each operation
    std::cout << "BST Insert Time: " << bstInsertTime << " microseconds" << std::endl;
    std::cout << "AVL Insert Time: " << avlInsertTime << " microseconds" << std::endl;
    std::cout << "(2,4) Insert Time: " << twoFourInsertTime << " microseconds" << std::endl;

    std::cout << "BST Search Time: " << bstSearchTime << " microseconds" << std::endl;
    std::cout << "AVL Search Time: " << avlSearchTime << " microseconds" << std::endl;
    std::cout << "(2,4) Search Time: " << twoFourSearchTime << " microseconds" << std::endl;

    std::cout << "BST Delete Time: " << bstDeleteTime << " microseconds" << std::endl;
    std::cout << "AVL Delete Time: " << avlDeleteTime << " microseconds" << std::endl;
    std::cout << "(2,4) Delete Time: " << twoFourDeleteTime << " microseconds" << std::endl;

    return 0;
}
