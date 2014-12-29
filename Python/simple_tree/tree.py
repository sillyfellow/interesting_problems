#!/usr/bin/python

from random import randint

class BinaryTree:
    def __init__(self, data):
        self.data = data
        self.rkid = None
        self.lkid = None
        self.count = 1

    def is_leaf(self):
        return (self.lkid == None) and (self.rkid == None)

    def height(self):
        if (not self.lkid) and (not self.rkid):
            return 0
        l, r = 0, 0
        if self.lkid:
            l = self.lkid.height()
        if self.rkid:
            r = self.rkid.height()
        return max(l, r) + 1

    def left_or_right(self, data):
        return randint(0, 1)

    def insert(self, data):
        choice = self.left_or_right(data)
        if choice == 0:
            if self.lkid:
                self.lkid.insert(data)
            else:
                self.lkid = self.__class__(data)
        elif choice == 1:
            if self.rkid:
                self.rkid.insert(data)
            else:
                self.rkid = self.__class__(data)
        else:
            self.count += 1

    def __repr__(self):
        string = ''
        if self.lkid:
            string += repr(self.lkid) + ", "
        string += ((repr(self.data) + ' ') * self.count).rstrip()
        if self.rkid:
            string += ", " + repr(self.rkid)
        return string

    def inorder_predecessor(self):
        if not self.lkid:
            return None
        node = self.lkid
        while node.rkid:
            node = node.rkid
        return node

    def inorder_successor(self):
        if not self.rkid:
            return None
        node = self.rkid
        while node.lkid:
            node = node.lkid
        return node

    @staticmethod
    def swap_nodes(node1, node2):
        data        = node1.data
        count       = node1.count
        node1.data  = node2.data
        node1.count = node2.count
        node2.data  = data
        node2.count = count

    def only_child(self):
        if not self.lkid:
            return self.rkid
        if not self.rkid:
            return self.lkid
        return None


class BinarySearchTree(BinaryTree):

    def left_or_right(self, data):
        if data == self.data:
            return 2
        return 0 if data < self.data else 1

    def swap_leaf_data(self):
        if self.is_leaf() or self.only_child():
            raise Exception("shall never reach here")

        choice = randint(0, 1)
        if choice == 0:
            node = self.inorder_predecessor()
        else:
            node = self.inorder_successor()
        self.swap_nodes(self, node)
        return choice

    def delete(self, data):
        if self.is_leaf():
            return None if self.data == data else self

        choice = self.left_or_right(data)
        if self.data == data: # i.e., choice is 2
            if self.only_child():
                return self.only_child()
            choice = self.swap_leaf_data()

        if choice == 0 and self.lkid:
            self.lkid = self.lkid.delete(data)
        elif choice == 1 and self.rkid:
            self.rkid = self.rkid.delete(data)
        return self

    def find(self, data):
        choice = self.left_or_right(data)

        if choice == 2:
            return self

        if choice == 0:
            return self.lkid.find(data) if self.lkid else None

        return self.rkid.find(data) if self.rkid else None

if __name__ == "__main__":
    limit = 100
    insertrands = [randint(1, limit) for x in range(limit / 3)]
    deleterands = [randint(1, limit) for x in range(limit / 2)]

    tree = BinarySearchTree(limit / 2)
    for x in insertrands:
        tree.insert(x)

    for d in deleterands:
        print "\n...Tree:...\n", tree
        print "Deleting: %d" % d
        if not tree.find(d):
            print "It is not in the tree, still you may try"

        tree = tree.delete(d)
        if randint(0, 3) == 1:
            print tree
            ins = randint(1, limit)
            print "\nInserting %d" % ins
            tree.insert(ins)
        print tree
        if not tree:
            break
