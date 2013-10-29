#include "utils.h"
/*
 * ===========================================================================
 *
 *       Filename:  utils.cc
 *
 *    Description:  simple utils.
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



vector<int> RandomArray(int lim = 16, int range=RAND_MAX)
{
	srand (time(NULL));
	vector<int> array;
	while(lim-- > 0)
	{
		int out = (rand() % range) - (range/2);
		array.push_back(out);
	}
	return array;
}
