#include "../solutions.h"
#include "../euler.h"

namespace euler{
	namespace problem1{

/******************************************************************************
 * Finds the sum of all multiples of 3 and 5 below 1000.
 */

/******************************************************************************
 * Brute force approach. Checks every number if it's a multiple and
 * adds is to the result.
 */
static long solution1(){
	long result = 0;
	for(long i = 0; i < 1000; ++i)
		if(i % 3 == 0 || i % 5 == 0)
			result += i;
	return result;
}
RegisterSolution(1, solution1);

/******************************************************************************
 * Calculate the sum of all numbers smaller than 1000 which can be divided by
 * num.
 * (e.g for num=3 the computations is:
 * 3+6+9+12+...+999 = 3*(1+2+3+4+...+333) = 3*(333+(333+1))/2;
 */
static long sumDivisibleBy(long num){
	//Find how many multiples there are for the specific number.
	// The target is 999 instead of 1000 because we want all the multiples
	// smaller than 1000.
	const long p = 999 / num; //integer division
	//and calculate the result.
	return num * (p *(p+1))/2;
}

/*
 * We use the inclusion/exclusion principle to calculate the result.
 * We add all the multiples of 3 and all the multiples of 5.
 * But now we have included twice the multiples of 15, so by excluding them,
 * we get the correct result.
 */
static long solution2(){
	long result = sumDivisibleBy(3) + sumDivisibleBy(5) - sumDivisibleBy(3*5);
	return result;
}

RegisterSolution(1, solution2);

// Close the namespaces
	} //problem1
} //euler

