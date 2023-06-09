import random
import time


# (2,4) Tree
class TwoFourNode:
    def __init__(self):
        self.keys = []
        self.children = []


class TwoFourTree:
    def __init__(self):
        self.root = None

    def insert(self, key):
        if self.root is None:
            self.root = TwoFourNode()
            self.root.keys.append(key)
        else:
            if len(self.root.keys) == 3:
                new_root = TwoFourNode()
                new_root.children.append(self.root)
                self.root = new_root
                self._split_child(self.root, 0)
            self._insert_recursive(self.root, key)

    def _insert_recursive(self, node, key):
        if isinstance(node.children, list) and node.children:
            index = self._find_index(node.keys, key)
            if index < len(node.keys) and key == node.keys[index]:
                return
            if len(node.children[index].keys) == 3:
                self._split_child(node, index)
                if key > node.keys[index]:
                    index += 1
            self._insert_recursive(node.children[index], key)
        else:
            index = self._find_index(node.keys, key)
            node.keys.insert(index, key)

    def search(self, key):
        return self._search_recursive(self.root, key)

    def _search_recursive(self, node, key):
        if node is None:
            return False
        index = self._find_index(node.keys, key)
        if index < len(node.keys) and key == node.keys[index]:
            return True
        if isinstance(node.children, list) and node.children:
            return self._search_recursive(node.children[index], key)
        return False

    def delete(self, key):
        if self.root is None:
            return
        self._delete_recursive(self.root, key)
        if len(self.root.keys) == 0:
            self.root = self.root.children[0]

    def _delete_recursive(self, node, key):
        index = self._find_index(node.keys, key)
        if index < len(node.keys) and key == node.keys[index]:
            if isinstance(node.children, list) and node.children:
                predecessor = node.children[index]
                while isinstance(predecessor.children, list) and predecessor.children:
                    predecessor = predecessor.children[-1]
                node.keys[index] = predecessor.keys[-1]
                key = predecessor.keys[-1]
                node = predecessor
                index = self._find_index(node.keys, key)
            node.keys.pop(index)
        if isinstance(node.children, list) and node.children:
            if len(node.children[index].keys) < 2:
                self._fix_child(node, index)
            self._delete_recursive(node.children[index], key)

    def _find_index(self, keys, key):
        for i in range(len(keys)):
            if key < keys[i]:
                return i
        return len(keys)

    def _split_child(self, parent, index):
        node = parent.children[index]
        new_node = TwoFourNode()
        parent.keys.insert(index, node.keys[1])
        parent.children.insert(index + 1, new_node)
        new_node.keys.append(node.keys[2])
        node.keys = node.keys[:1]

        if node.children:
            new_node.children.append(node.children[2])
            new_node.children.append(node.children[3])
            node.children = node.children[:2]

    def _fix_child(self, parent, index):
        if index > 0 and len(parent.children[index - 1].keys) > 2:
            self._rotate_right(parent, index)
        elif (
            index < len(parent.children) - 1
            and len(parent.children[index + 1].keys) > 2
        ):
            self._rotate_left(parent, index)
        else:
            if index == len(parent.children):
                index -= 1
            self._merge_children(parent, index)

    def _rotate_right(self, parent, index):
        node = parent.children[index]
        sibling = parent.children[index - 1]

        node.keys.insert(0, parent.keys[index - 1])
        parent.keys[index - 1] = sibling.keys.pop()
        if node.children:
            node.children.insert(0, sibling.children.pop())

    def _rotate_left(self, parent, index):
        node = parent.children[index]
        sibling = parent.children[index + 1]

        node.keys.append(parent.keys[index])
        parent.keys[index] = sibling.keys.pop(0)
        if node.children:
            node.children.append(sibling.children.pop(0))

    def _merge_children(self, parent, index):
        node = parent.children[index]
        sibling = parent.children[index + 1]

        node.keys.append(parent.keys.pop(index))
        node.keys.extend(sibling.keys)
        if node.children:
            node.children.extend(sibling.children)
        parent.children.pop(index + 1)


# Randomly populate the TwoFourTree
bst = TwoFourTree()
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
