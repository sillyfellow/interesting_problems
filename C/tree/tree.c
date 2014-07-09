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

node * create_new_node(int data)
{
  node * Node = malloc(sizeof(node));
  Node->left  = NULL;
  Node->right = NULL;
  Node->data  = data;
  Node->count = 1;
  return Node;
}

int is_leaf(node * tree)
{
  return (!tree->left && !tree->right);
}

node * get_only_child(node * tree)
{
  if (!tree->left)
    return tree->right;
  if (!tree->right)
    return tree->left;
  return NULL;
}

node * delete_leaf_node(node * tree, node * vater)
{
  if (!is_leaf(tree))
    return vater;

  if (tree)
    free(tree);

  if (!vater)
    return vater;

  if (tree == vater)
    tree = vater = NULL;
  else if(vater->left == tree)
    vater->left = NULL;
  else if (vater->right == tree)
    vater->right = NULL;
  return vater;
}

node * delete_node_with_only_one_child(node * tree, node * vater, node * onlykid)
{
  if(vater->left == tree)
    vater->left = onlykid;
  else if (vater->right == tree)
    vater->right = onlykid;
  if (tree)
    free(tree);
  return vater;
}

node * largest_from_left(node * tree)
{
  node * left = tree->left;
  while (left->right)
    left = left->right;
  return left;
}

node * smallest_from_right(node * tree)
{
  node * right = tree->right;
  while (right->left)
    right = right->left;
  return right;
}

void swap_node_with_viable_node_from_subtrees(node * tree)
{
  node * to_swap = NULL;
  if (rand() % 2)
    to_swap = smallest_from_right(tree);
  else
    to_swap = largest_from_left(tree);

  int data  = tree->data;  tree->data  = to_swap->data;  to_swap->data  = data;
  int count = tree->count; tree->count = to_swap->count; to_swap->count = count;
}

node * delete_node_from_tree(node * tree, node * vater, int data)
{
  if (!tree)
    return vater;

  if(data < tree->data)
  {
    tree = delete_node_from_tree(tree->left, tree, data);
    return vater;
  }

  if(data > tree->data)
  {
    tree = delete_node_from_tree(tree->right, tree, data);
    return vater;
  }

  /* now we are on the tree NODE to be deleted. */

  tree->count -= 1; /* reduce the count. */
  if (tree->count > 0)
    return vater;

  /* count has become zero, we have to really delete the stuff. */
  if(is_leaf(tree))
    return delete_leaf_node(tree, vater);

  node * onlykid = NULL;
  if((onlykid = get_only_child(tree)))
    return delete_node_with_only_one_child(tree, vater, onlykid);

  swap_node_with_viable_node_from_subtrees(tree);
  return delete_node_from_tree(tree, vater, data);
}

node * add_new_node_to_tree(node * tree, int data)
{
  if(tree == NULL)
    return create_new_node(data);
  if (data < tree->data)
    tree->left = add_new_node_to_tree(tree->left, data);
  if (data > tree->data)
    tree->right = add_new_node_to_tree(tree->right, data);
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
      printf("add: ");
      scanf("%d", &data);
      tree = add_new_node_to_tree(tree, data);
      continue;
    }

    if (input[0] == 'd'){
      printf("delete: ");
      scanf("%d", &data);
      tree = delete_node_from_tree(tree, tree, data);
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
  return 0;
}
