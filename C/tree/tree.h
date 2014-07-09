
/*
 * =====================================================================================
 *
 *       Filename:  tree.h
 *
 *    Description:  just so.. for no reason
 *
 *        Version:  1.0
 *        Created:  <can't remember>
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Sandeep Sadanandan (sillyfellow), grep@whybenormal.org
 *   Organization:  Galactic Sector ZZ9 Plural Z Alpha
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


struct TreeNode
{
    void * data;
    void * key;
    struct TreeNode ** kids;
    struct TreeNode *  dad;
};

typedef struct TreeNode TreeNode;

TreeNode * newTree(void * data, void * key);
TreeNode * insertInTree(TreeNode * tree, void * data, void * key);
void printTree(TreeNode * tree);

