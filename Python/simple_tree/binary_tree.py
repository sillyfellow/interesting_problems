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

