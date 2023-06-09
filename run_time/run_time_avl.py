import random
import time


# AVL Tree
class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1


class AVL:
    def __init__(self):
        self.root = None

    def insert(self, key):
        self.root = self._insert_recursive(self.root, key)

    def _insert_recursive(self, root, key):
        if root is None:
            return AVLNode(key)
        if key < root.key:
            root.left = self._insert_recursive(root.left, key)
        else:
            root.right = self._insert_recursive(root.right, key)
        root.height = 1 + max(self._get_height(root.left), self._get_height(root.right))
        balance = self._get_balance(root)
        if balance > 1 and key < root.left.key:
            return self._rotate_right(root)
        if balance < -1 and key > root.right.key:
            return self._rotate_left(root)
        if balance > 1 and key > root.left.key:
            root.left = self._rotate_left(root.left)
            return self._rotate_right(root)
        if balance < -1 and key < root.right.key:
            root.right = self._rotate_right(root.right)
            return self._rotate_left(root)
        return root

    def search(self, key):
        return self._search_recursive(self.root, key)

    def _search_recursive(self, root, key):
        if root is None or root.key == key:
            return root is not None
        if key < root.key:
            return self._search_recursive(root.left, key)
        else:
            return self._search_recursive(root.right, key)

    def delete(self, key):
        self.root = self._delete_recursive(self.root, key)

    def _delete_recursive(self, root, key):
        if root is None:
            return root
        if key < root.key:
            root.left = self._delete_recursive(root.left, key)
        elif key > root.key:
            root.right = self._delete_recursive(root.right, key)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left
            else:
                successor = self._find_minimum(root.right)
                root.key = successor.key
                root.right = self._delete_recursive(root.right, successor.key)
        root.height = 1 + max(self._get_height(root.left), self._get_height(root.right))
        balance = self._get_balance(root)
        if balance > 1 and self._get_balance(root.left) >= 0:
            return self._rotate_right(root)
        if balance < -1 and self._get_balance(root.right) <= 0:
            return self._rotate_left(root)
        if balance > 1 and self._get_balance(root.left) < 0:
            root.left = self._rotate_left(root.left)
            return self._rotate_right(root)
        if balance < -1 and self._get_balance(root.right) > 0:
            root.right = self._rotate_right(root.right)
            return self._rotate_left(root)
        return root

    def _find_minimum(self, root):
        while root.left is not None:
            root = root.left
        return root

    def _get_height(self, root):
        if root is None:
            return 0
        return root.height

    def _get_balance(self, root):
        if root is None:
            return 0
        return self._get_height(root.left) - self._get_height(root.right)

    def _rotate_left(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2
        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        return y

    def _rotate_right(self, z):
        y = z.left
        T3 = y.right
        y.right = z
        z.left = T3
        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        return y


# Randomly populate the AVL
bst = AVL()
random_data = random.sample(range(1000), 500)
for data in random_data:
    bst.insert(data)

# Measure runtime of insert operation
insert_data = random.randint(1001, 2000)
insert_start = time.time()
bst.insert(insert_data)
insert_end = time.time()
insert_time = insert_end - insert_start

# Measure runtime of search operation
search_data = random.choice(random_data)
search_start = time.time()
found = bst.search(search_data)
search_end = time.time()
search_time = search_end - search_start

# Measure runtime of delete operation
delete_data = random.choice(random_data)
delete_start = time.time()
bst.delete(delete_data)
delete_end = time.time()
delete_time = delete_end - delete_start

# Print the runtime of each operation
print("Insert Time:", insert_time)
print("Search Time:", search_time)
print("Delete Time:", delete_time)
