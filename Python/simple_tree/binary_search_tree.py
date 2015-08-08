#!/usr/bin/python

import binary_tree
from random import randint

class BinarySearchTree(binary_tree.BinaryTree):

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

