import random
import time


# Binary Search Tree Node
class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


# Binary Search Tree
class BinarySearchTree:
    def __init__(self):
        self.root = None

    # Insert a key into the BST
    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        else:
            self.insertRecursive(self.root, key)

    # Recursive helper function for insert operation
    def insertRecursive(self, node, key):
        if key < node.key:
            if node.left is None:
                node.left = Node(key)
            else:
                self.insertRecursive(node.left, key)
        else:
            if node.right is None:
                node.right = Node(key)
            else:
                self.insertRecursive(node.right, key)

    # Search for a key in the BST
    def search(self, key):
        return self.searchRecursive(self.root, key)

    # Recursive helper function for search operation
    def searchRecursive(self, node, key):
        if node is None or node.key == key:
            return node is not None
        elif key < node.key:
            return self.searchRecursive(node.left, key)
        else:
            return self.searchRecursive(node.right, key)

    # Delete a key from the BST
    def delete(self, key):
        self.root = self.deleteRecursive(self.root, key)

    # Recursive helper function for delete operation
    def deleteRecursive(self, node, key):
        if node is None:
            return node

        if key < node.key:
            node.left = self.deleteRecursive(node.left, key)
        elif key > node.key:
            node.right = self.deleteRecursive(node.right, key)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left

            temp = self.getMinValueNode(node.right)
            node.key = temp.key
            node.right = self.deleteRecursive(node.right, temp.key)

        return node

    # Get the node with the minimum key value in the BST
    def getMinValueNode(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current


# Function to generate a random number between min and max (inclusive)
def generateRandomNumber(min_val, max_val):
    return random.randint(min_val, max_val)


# Function to measure runtime of a function
def measureRuntime(func):
    start_time = time.time()
    func()
    end_time = time.time()
    return end_time - start_time


if __name__ == "__main__":
    # Create an instance of the Binary Search Tree
    bst = BinarySearchTree()

    # Generate a random list of numbers for testing
    num_elements = 10000
    min_key = 1
    max_key = num_elements * 10
    random.seed(time.time())

    for _ in range(num_elements):
        key = generateRandomNumber(min_key, max_key)
        bst.insert(key)

    # Measure the runtime of operations
    search_key = generateRandomNumber(min_key, max_key)

    insert_runtime = measureRuntime(
        lambda: bst.insert(generateRandomNumber(min_key, max_key))
    )
    search_runtime = measureRuntime(lambda: bst.search(search_key))
    delete_runtime = measureRuntime(lambda: bst.delete(search_key))

    # Print the runtimes
    print("Binary Search Tree Runtimes:")
    print("Insertion: {:.6f} seconds".format(insert_runtime))
    print("Search: {:.6f} seconds".format(search_runtime))
    print("Deletion: {:.6f} seconds".format(delete_runtime))
