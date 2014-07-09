/*
 * =====================================================================================
 *
 *       Filename:  tree.c
 *
 *    Description:  a simple file which I typed in at some point of
 *                  time, .. just so.
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

#include "tree.h"

node * newnode(int data)
{
  node * Node = malloc(sizeof(node));
  Node->left = NULL;
  Node->right = NULL;
  Node->data = data;
  Node->count = 1;
  return Node;
}

int isleaf(node * tree)
{
  return ((tree->left == NULL) && (tree->right == NULL));
}

node * single_kid(node * tree)
{
  if ((tree->left == NULL) && (tree->right != NULL))
    return tree->right;
  if ((tree->left != NULL) && (tree->right == NULL))
    return tree->left;
  return NULL;
}

int replace(node * tree, node * father)
{
  int randm = rand() % 2;
  switch(randm)
  {
    case 0:
      break;
    case 1:
      break;
    default:
      break;
  }
}

void treedel(node * tree, node * vater, int data)
{
  int random = 0;
  node * onlykid = NULL;
  if (tree == NULL)
    return; /* nothing to delete */
  if(data < tree->data)
  { /* happens to be in the left tree */
    treedel(tree->left, tree, data);
  }
  if(data > tree->data)
  { /* let's delete it from the right subtree. */
    treedel(tree->right, tree, data);
  }
  /* now we are on the tree NODE to be deleted. */

  tree->count -= 1; /* reduce the count. */
  if (tree->count != 0)
    return; /* just return. */

  /* count has become zero, we have to really delete the stuff. */

  if(tree == vater) /*  happens to be the root node. */
  {
    if(isleaf(tree)) /* the only node in the tree */
    {
      free(tree);
      return ;
    }

  }
  else
  {
    if(isleaf(tree))
    {
      if(vater->left == tree)
      {
        free(tree);
        vater->left = NULL;
      }
      else if (vater->right == tree)
      {
        free(tree);
        vater->right = NULL;
      }
      else
      {
        /* this should not happen */
      }
    }

    if((onlykid = single_kid(tree)) != NULL)
    {/* if tree has only one child, we can replace tree by it's kid. */
      if(vater->left == tree)
      {
        vater->left = onlykid;
      }
      else if (vater->right == tree)
      {
        vater->right = onlykid;
      }
      else
      {
        /* this should not happen */
      }
      free(tree); /* you can free it now. */
    }

    /* not a leaf, nor the father of only one child - */
    /* hence replace tree with leftmost child of right child or */
    /* rightmost child of left child */
    /* random == 1 --> left child's rightmost child and */
    /* random == 2 --> the other option. */

    random = replace(tree, vater); /* does the random replacement. */
    if(random == 1)
      treedel(tree->left, tree, data);
    else if (random == 2)
      treedel(tree->right, tree, data);
    else
      ;
    /* this is not supposed to happen. */
  }

}

node * treeadd(node * tree, int data)
{
  if(tree == NULL)
    return newnode(data);
  if (data < tree->data)
    tree->left = treeadd(tree->left, data);
  if (data > tree->data)
    tree->right = treeadd(tree->right, data);
  if (data == tree->data)
    tree->count++;
  return tree;
}

void inorder(node * tree)
{
  if(tree == NULL)
    return;
  inorder(tree->left);
  printf("%d ", tree->data);
  inorder(tree->right);
}

int main()
{
  int data = 0;
  int c;
  char * input = malloc(1024*sizeof(char));
  node * tree = NULL;
  printf("Try a, d, p or q (for add, delete, print and quit respectively)\n");
  while(gets(input) != NULL)
  {
    if (strlen(input) == 0) /* blank line */
      continue;

    /* Note: I am not checking for the right kind of inputs. */
    /* The focus is on the algorithms. */
    if(input[0] == 'a'){
      printf("Give the number: ");
      scanf("%d", &data);
      tree = treeadd(tree, data);
      continue;
    }

    if (input[0] == 'd'){
      printf("Give the number: ");
      scanf("%d", &data);
      treedel(tree, tree, data);
      continue;
    }

    if (input[0] == 'p'){
      printf("\n");
      inorder(tree);
      printf("\n");
      continue;
    }

    if (input [0] == 'q')
      break;

    printf("Invalid input: Try a, d, p or q (for add, delete, print and quit respectively).\n");
  }

  printf("Good bye\n");
}
