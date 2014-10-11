#include "../solutions.h"

namespace euler{
	namespace problem6{

long solution(){
	long sumSquares = 0;
	for(long i=1; i <= 100; ++i)
		sumSquares += i*i;
	
	long squareSum = 100*101/2;
	squareSum *= squareSum;

	return squareSum - sumSquares;
}

RegisterSolution(6, solution);

	} // problem6
} // euler

