#include "../solutions.h"
#include "../euler.h"

namespace euler{
	namespace problem15{

/*
 * The number of paths for the grid positions equal to the corresponding
 * number of a pascal triangle.
 *
 * We construct a pascal triangle and then we get the result.
 */
static long solution(){
	// 21 because we need the pbox[20][20]
	auto pbox = euler::pascalBox<long>(21);
	//euler::printTable(pb);
	return pbox[20][20];
}

RegisterSolution(15, solution);

/*
 * The number of paths are the central binomial coefficients, central meaning
 * they fall along the center line of Pascal's triangle.
 * So the solution is (2n)!/(n!^2)
 */
static long solution2(){
	long result = 1;
	const long n = 20;
	//overflows
	//result = euler::factorial(2*n)/(euler::factorial(n)*euler::factorial(n));

	/* We turn the f(n)=(2n)!/(n!*n!) into an iterative function and hope that
	 * the intermediate operations don't overflow.
	 *
	 * So, the final iterative function is:
	 *     f(1) = 2
	 *     f(n) = f(n-1)*2*(2n-1)/n
	 */

	 // value for f(1)
	 result = 2;
	 for(long i = 2; i <= n; ++i){
	 	// apply the iterative step
		// result = (f(i-1)==previous result)*2*(2*i-1)/i
		result = result * 2*(2*i-1)/i;
	}


	return result;
}

RegisterSolution(15, solution2);

	} // problem15
} // euler

