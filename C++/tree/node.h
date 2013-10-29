/*
 * ===========================================================================
 *
 *       Filename:  binary_tree.h
 *
 *    Description:  Just trying out to create some data structures in C++.
 *					Here's a random node of a tree.
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

#ifndef NODE_H
#define NODE_H 

#include "utils.h"
template <typename T> 
class Node {


	public:
	T data;
	Node * left;
	Node * right;

	Node (T info, Node * l = NULL, Node * r = NULL) 	{
		data  = info;
		left  = l;
		right = r;
	}

	~Node()
	{
//		cout << "Deleting " << data << endl;
		Delete(left);
		Delete(right);
	}

	static void Delete (Node * ptr)
	{
		if (ptr != NULL)
			delete ptr;
		ptr = NULL;
	}
};

#endif
