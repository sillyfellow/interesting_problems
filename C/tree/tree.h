
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

typedef struct node {
  struct node * left;
  struct node * right;
  int data;
  int count;
} node;

