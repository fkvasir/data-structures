#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// (2,4) Tree Node
struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
};

// (2,4) Tree
class TwoFourTree {
public:
    TwoFourTree() {
        root = nullptr;
    }

    // Insert a key into the (2,4) tree
    void insert(int key) {
        if (root == nullptr) {
            root = new Node();
            root->keys.push_back(key);
        } else {
            Node* newChild = nullptr;
            bool inserted = insertRecursive(root, key, newChild);
            if (inserted) {
                if (newChild != nullptr) {
                    Node* oldRoot = root;
                    root = new Node();
                    root->keys.push_back(newChild->keys[0]);
                    root->children.push_back(oldRoot);
                    root->children.push_back(newChild);
                }
            }
        }
    }

    // Search for a key in the (2,4) tree
    bool search(int key) {
        return searchRecursive(root, key);
    }

    // Delete a key from the (2,4) tree
    void remove(int key) {
        removeRecursive(root, key);
        if (root != nullptr && root->keys.empty()) {
            Node* oldRoot = root;
            if (root->children.size() == 1) {
                root = root->children[0];
            }
            delete oldRoot;
        }
    }

private:
    // Find the index to insert a key in a node
    int findInsertIndex(const std::vector<int>& keys, int key) {
        int index = 0;
        while (index < keys.size() && key > keys[index])
            index++;
        return index;
    }

    // Insert a key into the (2,4) tree (recursive helper function)
    bool insertRecursive(Node* node, int key, Node*& newChild) {
        if (node == nullptr)
            return false;

        int insertIndex = findInsertIndex(node->keys, key);
        if (insertIndex < node->keys.size() && node->keys[insertIndex] == key)
            return false; // Duplicate keys are not allowed

        if (node->children.empty()) {
            node->keys.insert(node->keys.begin() + insertIndex, key);
            if (node->keys.size() > 3) {
                splitNode(node, newChild);
                return true;
            }
            return false;
        } else {
            Node* child = node->children[insertIndex];
            bool inserted = insertRecursive(child, key, newChild);
            if (inserted) {
                if (newChild != nullptr) {
                    node->keys.insert(node->keys.begin() + insertIndex, newChild->keys[0]);
                    node->children.insert(node->children.begin() + insertIndex + 1, newChild);
                    if (node->keys.size() > 3)
                        splitNode(node, newChild);
                    else
                        newChild = nullptr;
                }
                return true;
            }
            return false;
        }
    }

    // Split a node into two nodes
    void splitNode(Node* node, Node*& newChild) {
        int midIndex = node->keys.size() / 2;
        int midKey = node->keys[midIndex];

        Node* leftNode = new Node();
        leftNode->keys.insert(leftNode->keys.begin(), node->keys.begin(), node->keys.begin() + midIndex);
        if (!node->children.empty()) {
            leftNode->children.insert(leftNode->children.begin(), node->children.begin(), node->children.begin() + midIndex + 1);
            node->children.erase(node->children.begin(), node->children.begin() + midIndex + 1);
        }

        Node* rightNode = new Node();
        rightNode->keys.insert(rightNode->keys.begin(), node->keys.begin() + midIndex + 1, node->keys.end());
        if (!node->children.empty()) {
            rightNode->children.insert(rightNode->children.begin(), node->children.begin() + midIndex + 1, node->children.end());
            node->children.erase(node->children.begin() + midIndex + 1, node->children.end());
        }

        newChild = rightNode;

        node->keys.clear();
        node->keys.push_back(midKey);
        node->children.push_back(leftNode);
        node->children.push_back(rightNode);
    }

    // Search for a key in the (2,4) tree (recursive helper function)
    bool searchRecursive(Node* node, int key) {
        if (node == nullptr)
            return false;

        int searchIndex = findInsertIndex(node->keys, key);
        if (searchIndex < node->keys.size() && node->keys[searchIndex] == key)
            return true;

        if (node->children.empty())
            return false;

        Node* child = node->children[searchIndex];
        return searchRecursive(child, key);
    }

    // Delete a key from the (2,4) tree (recursive helper function)
    void removeRecursive(Node* node, int key) {
        if (node == nullptr)
            return;

        int deleteIndex = findInsertIndex(node->keys, key);
        if (deleteIndex < node->keys.size() && node->keys[deleteIndex] == key) {
            if (node->children.empty()) {
                node->keys.erase(node->keys.begin() + deleteIndex);
            } else {
                Node* predNode = node->children[deleteIndex];
                int predKey = predecessor(predNode);
                node->keys[deleteIndex] = predKey;
                removeRecursive(predNode, predKey);
            }
        } else {
            Node* child = node->children[deleteIndex];
            if (child != nullptr) {
                if (child->keys.size() == 1) {
                    Node* leftSibling = (deleteIndex > 0) ? node->children[deleteIndex - 1] : nullptr;
                    Node* rightSibling = (deleteIndex < node->children.size() - 1) ? node->children[deleteIndex + 1] : nullptr;
                    if (leftSibling != nullptr && leftSibling->keys.size() > 1) {
                        child->keys.insert(child->keys.begin(), node->keys[deleteIndex - 1]);
                        node->keys[deleteIndex - 1] = leftSibling->keys.back();
                        leftSibling->keys.pop_back();
                        if (!leftSibling->children.empty()) {
                            child->children.insert(child->children.begin(), leftSibling->children.back());
                            leftSibling->children.pop_back();
                        }
                    } else if (rightSibling != nullptr && rightSibling->keys.size() > 1) {
                        child->keys.push_back(node->keys[deleteIndex]);
                        node->keys[deleteIndex] = rightSibling->keys.front();
                        rightSibling->keys.erase(rightSibling->keys.begin());
                        if (!rightSibling->children.empty()) {
                            child->children.push_back(rightSibling->children.front());
                            rightSibling->children.erase(rightSibling->children.begin());
                        }
                    } else {
                        if (leftSibling != nullptr) {
                            mergeNodes(leftSibling, node, deleteIndex - 1);
                            child = leftSibling;
                        } else if (rightSibling != nullptr) {
                            mergeNodes(child, node, deleteIndex);
                        }
                    }
                }
                removeRecursive(child, key);
            }
        }
    }

    // Find the predecessor key in a node
    int predecessor(Node* node) {
        while (!node->children.empty()) {
            node = node->children.back();
        }
        return node->keys.back();
    }

    // Merge two nodes together
    void mergeNodes(Node* leftNode, Node* parent, int mergeIndex) {
        Node* rightNode = parent->children[mergeIndex + 1];

        leftNode->keys.push_back(parent->keys[mergeIndex]);
        leftNode->keys.insert(leftNode->keys.end(), rightNode->keys.begin(), rightNode->keys.end());
        if (!rightNode->children.empty()) {
            leftNode->children.insert(leftNode->children.end(), rightNode->children.begin(), rightNode->children.end());
        }

        parent->keys.erase(parent->keys.begin() + mergeIndex);
        parent->children.erase(parent->children.begin() + mergeIndex + 1);

        delete rightNode;
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
    TwoFourTree tree;
    // Generate a random list of numbers for testing
    const int numElements = 500;
    const int minKey = 1;
    const int maxKey = numElements * 10;
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < numElements; ++i) {
        int key = generateRandomNumber(minKey, maxKey);
        tree.insert(key);
    }

    // Measure the runtime of operations
    const int searchKey = generateRandomNumber(minKey, maxKey);

    double insertRuntime = measureRuntime([&tree, minKey, maxKey]() {
        for (int i = 0; i < numElements; ++i) {
            int key = generateRandomNumber(minKey, maxKey);
            tree.insert(key);
        }
    });

    double searchRuntime = measureRuntime([&tree, searchKey]() {
        tree.search(searchKey);
    });

    double deleteRuntime = measureRuntime([&tree, searchKey]() {
        tree.remove(searchKey);
    });

    // Print the runtimes
    std::cout << "(2,4) Tree Runtimes:" << std::endl;
    std::cout << "Insertion: " << insertRuntime << " seconds" << std::endl;
    std::cout << "Search: " << searchRuntime << " seconds" << std::endl;
    std::cout << "Deletion: " << deleteRuntime << " seconds" << std::endl;

    return 0;
}
