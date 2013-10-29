/*
 * ===========================================================================
 *
 *       Filename:  binary_tree.h
 *
 *    Description:  Test the binary_tree and binary_search_tree. Just very
 *					basic test. No special routine for testing. Directly
 *					testing from main.cc (see the compiler flag).
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Sadanandan (GS ZZ9 Plural Zα), sandeep.nellayi at gmx.de
 *        Company:  None
 *
 * ===========================================================================
 */

#include "utils.h"
#include "binary_tree.h"
#include "binary_search_tree.h"

int main(int argc, char *argv[])
{
	cout << "What a lovely day!" << endl;
#ifndef PLAINTREE
	BinarySearchTree<int> tree;
	cout << "Going to create a binary search tree with random elements:" << endl << endl;
#else
	BinaryTree<int> tree;
	cout << "Going to create a normal binary tree with random elements:" << endl << endl;
#endif
	vector<int>elements = RandomArray(20, 64);
	for(vector<int>::iterator it = elements.begin(); it != elements.end(); it++) 
	{
		cout << setw(4) << *it << ", ";
		tree.BinaryTree::insert(*it);
	}

	cout << endl << "Tree created " << endl << "And looks like this in Inorder traversal" << endl << endl;
	tree.inorder();
	cout << endl;

	cout << "Attempting to delete a few elements" << endl << endl;
	vector<int>tofind = RandomArray(10, 64);
	for(vector<int>::iterator it = tofind.begin(); it != tofind.end(); it++) 
	{ 
		cout << "Looking for " << setw(4) << *it << " ";
		Node<int> * node = tree.BinaryTree::search(*it);
		if (node != NULL)
		{
			cout << " ...found it.." << setw(4)  << *it;
			tree.remove(*it);
			cout << " ... and removed it!" << endl;
		}
		else
			cout << " ...not available" << endl;
	}

	cout << endl << endl;
	tree.inorder();
	cout << endl;
	
	return 0;
}
