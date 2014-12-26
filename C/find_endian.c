/*
 * ===========================================================================
 *
 *       Filename:  find_endian.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/11/2011
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Sadanandan (GS ZZ9 Plural Zα)
 *
 * ===========================================================================
 */

#include <stdio.h>

typedef union
{
  int i;
  char c[4];
}u;

int main()
{
  u temp;
  temp.i = 0x12345678;

  printf("%x\n", temp.i);
  printf("%x %x %x %x\n", temp.c[0], temp.c[1], temp.c[2], temp.c[3]);
}


