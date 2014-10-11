#include "../solutions.h"

namespace euler{
	namespace problem9{

bool isSolution(long a, long b, long c){
	return (a*a + b*b) == c*c;
}

long getC(long a, long b){
	return 1000-a-b;
}

long getB(long a){
	if(a == 1000)
		return 0;
	
	return 1000*(a-500)/(a-1000);
}

/*
 * By working with the problem, we can express the numbers b and c based on a.
 * So we go through numbers and try to find an a that makes all other
 * restrictions fall into place.
 */
long solution(){
	//natural numbers, so a=0 isn't an accepted solution.
	for(long a = 1; ; ++a){
		long b = getB(a);
		long c = getC(a, b);
		if(isSolution(a, b, c))
			return a*b*c;
	}

	//if it didn't find a solution return -1 as an indication of error
	return -1;
}

RegisterSolution(9, solution);

	} // problem9
} // euler

