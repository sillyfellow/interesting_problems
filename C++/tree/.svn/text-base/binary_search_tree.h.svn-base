/*
 * ===========================================================================
 *
 *       Filename:  binary_search_tree.h
 *
 *    Description:  Just trying out to create some data structures in C++.
 *					Here is the famous binary search tree.					
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

#ifndef BINSEARCHTREE
#define BINSEARCHTREE

#include "binary_tree.h"
#include "utils.h"
#include "node.h"

template <typename T> 
class BinarySearchTree : public BinaryTree<T>
{
	private:
		virtual bool LeftCouldContain(Node<T> * &node, T &data);
		virtual bool RightCouldContain(Node<T> * &node, T &data);
		virtual void insert(Node<T> * &node, T &data);
		virtual Node<T> * search(Node<T> * &node, T &data);

	// none of the public methods need to be inherited from binary tree.
	// they're all implemented with the four private methods.
	// Note: search needs to be implemented here, because the search in binary
	// tree is a DFS/BFS. With binary_search_tree, we know which branch to
	// choose.
};

template <typename T>
bool BinarySearchTree<T>::LeftCouldContain(Node<T> * &node, T &data)
{
	return (node != NULL) && (data < node->data);
}

template <typename T>
bool BinarySearchTree<T>::RightCouldContain(Node<T> * &node, T &data)
{
	return (node != NULL) && (data > node->data);
}

template <typename T>
void BinarySearchTree<T>::insert(Node<T> * &node, T &data)
{
	if (node == NULL)
	{
		node = new Node<T>(data);
		return;
	}

	if (data < node->data)
		insert(node->left, data);
	else if (data > node->data)
		insert(node->right, data);
	else 
		cout << endl << "The tree already contains: " << data << ", skipping.." << endl << endl;
}

template <typename T>
Node<T> * BinarySearchTree<T>::search(Node<T> * &node, T &data)
{
	if ((node == NULL) || (node->data == data))
		return node;
	if (data < node->data)
		return search(node->left, data);
	return search(node->right, data);
}

#endif
