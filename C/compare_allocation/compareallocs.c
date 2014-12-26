/*
 * ===========================================================================
 *
 *       Filename:  compareallocs.c
 *
 *    Description:  compare malloc/calloc/or-alloting+zeroing
 *
 *        Version:  1.0
 *        Created:  10/13/2011
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Sadanandan (GS ZZ9 Plural Zα)
 *
 * ===========================================================================
 */


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

time_t before;
time_t after;

#define start() before = time(&before)
#define stop()  after  = time(&after)
#define diff_time() ((int)(after - before))

static int just_malloc(int num)
{
  int timetaken = 0;
  for( int i = 0; i < num; i += 1)
  {
    start();
    char ** biggarray = malloc(num*sizeof(char*));
    for( int j = 0; j < num; j += 1)
    {
      biggarray[j] = malloc(1024*sizeof(char));
    }
    stop();

    for( int j = 0; j < num; j += 1)
    {
      free(biggarray[j]);
    }
    free(biggarray);
    timetaken += diff_time();
  }
  return timetaken;
}

static int just_calloc(int num)
{
  int timetaken = 0;
  for( int i = 0; i < num; i += 1)
  {
    start();
    char ** biggarray = calloc(num, sizeof(char*));
    for( int j = 0; j < num; j += 1)
    {
      biggarray[j] = calloc(1024, sizeof(char));
    }
    stop();

    for( int j = 0; j < num; j += 1)
    {
      free(biggarray[j]);
    }
    free(biggarray);
    timetaken += diff_time();
  }
  return timetaken;
}


static void callocking_for_zero(int size)
{
  char * mem = calloc(size, sizeof(char));
  free(mem);
}

static void mallocking_and_zero(int size)
{
  char * mem = malloc(size*sizeof(char));
  memset(mem, 0, size);
  free(mem);
}

static void allocate_and_memset(int size)
{
  char mem[size];// = malloc(size*sizeof(char));
  memset(mem, 0, size);
}

static int compare_zeroing_allocs(int count)
{
  int tcalloc, tmalloc, tdirect;
  tcalloc = tmalloc = tdirect = 0;
  for( int i = 0; i < 1024; i += 1)
  {
    start();
    for( int j = 0; j < count; j += 1)
    {
      callocking_for_zero(1024);
      callocking_for_zero(1025);
      callocking_for_zero(2049);
    }
    stop();
    tcalloc += diff_time();

    start();
    for( int j = 0; j < count; j += 1)
    {
      mallocking_and_zero(1024);
      mallocking_and_zero(1025);
      mallocking_and_zero(2049);
    }
    stop();
    tmalloc += diff_time();

    start();
    for( int j = 0; j < count; j += 1)
    {
      allocate_and_memset(1024);
      allocate_and_memset(1025);
      allocate_and_memset(2049);
    }
    stop();
    tdirect += diff_time();
  }
  printf("For %d\n Calloc: %d \n Malloc: %d \n Direct: %d\n", (count * 1024 * 3), tcalloc, tmalloc, tdirect);
  return 0;
}



static int Usage()
{
  printf("Usage: compareallocs <count>\n");
  return -127;
}

int main (int argc, char const* argv[])
{

  /*  RESULT:
   *  direct allocation and memset is faster than anything else.
   *  then malloc is faster and then comes calloc
   *  */
  if (argc < 2)
    return Usage();
  int count = atoi(argv[1]);
  return compare_zeroing_allocs(count);
  printf("Malloc (%d):%d  and Calloc(%d):%d\n", count, just_malloc(count), count, just_calloc(count));
  printf("Calloc (%d):%d  and Malloc(%d):%d\n", count, just_calloc(count), count, just_malloc(count));

  return 0;
}



