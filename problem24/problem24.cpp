#include "../solutions.h"
#include <string>
#include <algorithm>

namespace euler{
	namespace problem24{

/******************************************************************************
 * Returns the 1000000th permutation of the string 0123456789
 */
long solution()
{
	std::string str="0123456789";

	// the initial string is the 1st permutation
	// we need 999999 more to get the desired one
	for(long perm = 1; perm < 1000000; ++perm)
	{
		std::next_permutation(str.begin(), str.end());
	}

	//convert string to long to return it on the appropriate type
	return atol(str.c_str());
}

RegisterSolution(24, solution);

	} // problem24
} // euler

