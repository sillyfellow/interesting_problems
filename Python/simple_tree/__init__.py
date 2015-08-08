#!/usr/bin/python

import binary_search_tree
from random import randint

def main():
    limit = 100
    insertrands = [randint(1, limit) for x in range(limit / 3)]
    deleterands = [randint(1, limit) for x in range(limit / 2)]

    tree = binary_search_tree.BinarySearchTree(limit / 2)
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


if __name__ == "__main__":
    main()
