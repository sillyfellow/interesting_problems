/*
 * ===========================================================================
 *
 *       Filename:  binary_tree.h
 *
 *    Description:  Just trying out to create some data structures in C++.
 *					Here is the basic binary tree with the basic
 *					insert/search/remove operations. I try to do the insertion
 *					on a randomly chosen side. So as to keep the tree more or
 *					less balanced. Also, during deletion of an internal node,
 *					the leaf which would replace comes randomly from from left
 *					of right. Again, some minute balancing happens there.
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
#ifndef BINTREE
#define BINTREE

#include "utils.h"
#include "node.h"

template <typename T> 
class BinaryTree {
	private:
		Node<T> * root;

		// need overriding later.
		virtual bool LeftCouldContain(Node<T> * &node, T &data);
		virtual bool RightCouldContain(Node<T> * &node, T &data);
		virtual void insert(Node<T> * &node, T &data);
		virtual Node<T> * remove(Node<T> * &node, T &data);
		virtual Node<T> * search(Node<T> * &node, T &data);

		// the same behaviour for all types of binary trees.
		void DeleteTree(Node<T> * &node); // currently not necessary to be virtual.
		void inorder(Node<T> * &node);
		Node<T> * InorderPredecessor(Node<T> * &node);
		Node<T> * InorderSuccessor(Node<T> * &node);
		Node<T> * LeftMostElement(Node<T> * &node);
		Node<T> * RightMostElement(Node<T> * &node);

	public: // none of these need to be virtual

		void inorder();
		void insert(T &data);
		Node<T> * search(T &data);
		void remove(T &data);

		BinaryTree()
		{
			root = NULL;
			srand (time(NULL));
		}

		~BinaryTree()
		{
			DeleteTree(root);
		}
};

template<typename T>
void BinaryTree<T>::inorder()
{
	cout << endl << "The BinaryTree: ";
	inorder(root);
	cout << endl;
}

template<typename T>
void BinaryTree<T>::insert(T &data)
{
	insert(root, data);
}

template<typename T>
Node<T> * BinaryTree<T>::search(T &data)
{
	return search(root, data);
}

template<typename T>
void BinaryTree<T>::remove(T &data)
{
	root = remove(root, data);
}

template <typename T>
void BinaryTree<T>::DeleteTree(Node<T> * &node)
{
	Node<T>::Delete(node);
}

template <typename T>
void BinaryTree<T>::inorder(Node<T> * &node)
{
	if (node == NULL)
		return;

	inorder(node->left);
	cout << " " << node->data;
	inorder(node->right);
}

template <typename T>
void BinaryTree<T>::insert(Node<T> * &node, T &data)
{
	if (node == NULL)
	{
		node = new Node<T>(data);
		return;
	}

	// randomly pick a side to go.
	if (rand() % 2 == 1)
		insert(node->left, data);
	else
		insert(node->right, data);
}

template <typename T>
Node<T> * BinaryTree<T>::search(Node<T> * &node, T &data)
{
	if ((node == NULL) || (node->data == data))
		return node;
	Node<T> * has_on_left = search(node->left, data);
	if (has_on_left != NULL)
		return has_on_left;
	return search(node->right, data);
}

template <typename T>
Node<T> * BinaryTree<T>::LeftMostElement(Node<T> * &node)
{
	if (node == NULL)
		return NULL;
	Node<T> * tmp = node;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}

template <typename T>
Node<T> * BinaryTree<T>::RightMostElement(Node<T> * &node)
{
	if (node == NULL)
		return NULL;
	Node<T> * tmp = node;
	while (tmp->right != NULL)
		tmp = tmp->right;
	return tmp;
}

template <typename T>
Node<T> * BinaryTree<T>::InorderSuccessor(Node<T> * &node)
{
	if (node == NULL)
		return NULL;
	return LeftMostElement(node->right);
}

template <typename T>
Node<T> * BinaryTree<T>::InorderPredecessor(Node<T> * &node)
{
	if (node == NULL)
		return NULL;
	return RightMostElement(node->left);
}

template <typename T>
bool BinaryTree<T>::LeftCouldContain(Node<T> * &node, T &data)
{
	return (node != NULL) && (search(node->left, data) != NULL);
}

template <typename T>
bool BinaryTree<T>::RightCouldContain(Node<T> * &node, T &data)
{
	return (node != NULL) && (search(node->right, data) != NULL);
}

template <typename T>
Node<T> * BinaryTree<T>::remove(Node<T> * &node, T &data)
{
	if (node == NULL)
		return node;

	// if this is not the node.
	if (node->data != data)
	{
		// if on the left side.
		if (LeftCouldContain(node, data))
			node->left = remove(node->left, data);

		// else if on the right side. 
		// (without "else", we might delete it from the other side).
		else if (RightCouldContain(node, data))
			node->right = remove(node->right, data);

		// perhaps changes were made in the subtrees. 
		// return the current root.
		return node;
	}

	// This IS THE node.

	// if leaf
	if ((node->left == NULL) && (node->right == NULL))
	{
		delete node;
		return NULL;
	}

	// if the parent of one child.
	if ((node->left == NULL) || (node->right == NULL))
	{
		Node<T> * onlychild = (node->left == NULL) ? node->right : node->left;
		node->left = NULL;
		node->right = NULL;
		delete node;
		return onlychild;
	}

	// some midway node with two kids.
	// pick a possible leaf node from one of the sides.
	bool leftside = (rand() % 2) == 1;
	Node<T> * candidate = leftside ? InorderPredecessor(node) : InorderSuccessor(node);

	T tmp           = node->data;
	node->data      = candidate->data;
	candidate->data = tmp;

	if (leftside)
		node->left = remove(node->left, tmp);
	else 
		node->right = remove(node->right, tmp);

	return node;
}
#endif
