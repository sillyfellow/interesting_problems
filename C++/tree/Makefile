
all: bintree bstree

bintree: utils.cc main.cc binary_search_tree.h binary_tree.h node.h
	g++ utils.cc main.cc -DPLAINTREE -o bintree

bstree: utils.cc main.cc binary_search_tree.h binary_tree.h node.h
	g++ utils.cc main.cc -o bstree

clean:
	rm -rf *~ a.out bintree bstree *.o tags
