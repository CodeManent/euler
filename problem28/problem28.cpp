#include "../solutions.h"
#include <iostream>

static long solution()
{
	unsigned long result = 1;
	unsigned long current = 1;
	//we expand the size of the square 
	for(unsigned long size = 3; size <= 1001; size += 2){
		//and for each square, we grab the corners
		for(unsigned long i = 0; i < 4; ++i){
			// one corner is size steps away from the next.
			current += size-1;
			result += current;
		}
	}

	return result;
}

RegisterSolution(28, solution);

