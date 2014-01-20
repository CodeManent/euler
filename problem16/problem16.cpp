#include "../solutions.h"
#include "../bignum.h"

/*
 * The 2^1000 can be calculated by doubling 1 1000 times.
 * So after calculating the number, we sum its digits and return the result.
 */
long solution(){
	euler::BigNum accumulator("1");
	
	for(long i=0; i < 1000; ++i)
		accumulator = accumulator + accumulator;

	return accumulator.sumDigits();
}

RegisterSolution(16, solution);

