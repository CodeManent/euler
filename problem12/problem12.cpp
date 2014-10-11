#include "../solutions.h"
#include "../euler.h"

namespace euler {
	namespace problem12 {

/*
 * The solution exploits that the triangular numbers can be written as n(n+1)/2,
 * Either n or n+1 is even each time so se put on the even one the /2.
 * The number of factors the number has is computed by multiplying the factors
 * on n and n+1.
 * The factors of n don't need to be computed on the iteration step as they have
 * already been computed on the previous iteration (for the n+1 then, n now).
 */
long solution(){
	auto nfactors = 1L;
	auto n1factors = 2L;
	long result = 0;
	long maxFactors = 0;
	long n = 1;
	long n1 = 1;

	for(long i=3;  ; ++i){
		n = n1;
		nfactors = n1factors;

		n1 = i+1;
		// if n+1 is even, push the /2 part on it
		if(n1 % 2 == 0){
			n1 = n1 / 2;
		}
		/*
		else
		n is the even one and has alrealy been divided by 2 on the previous
		iteration. so the current value of n is actually the n/2 part of the 
		n(n+1)/2
		*/
		n1factors = euler::countFactors(n1);

		if(nfactors * n1factors > maxFactors)
			maxFactors = nfactors * n1factors;

		if(maxFactors > 500){
			//the /2 has already been computed on the n1 computation for each
			//iteration.
			result = n*n1;
			break;
		}
	}
	return result;
}

RegisterSolution(12, solution);

	} // problem12
} // euler

