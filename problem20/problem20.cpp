#include "../solutions.h"
#include "../bignum.h"
#include <iostream>

/*
 * Returns the sum of the digits in the 100!
 */
static long solution(){
	euler::BigNum bn("1");
	//compute the 100!
	for(long i = 1; i <= 100; ++i)
	{
		bn = bn * i;
		//std::cout << i << "! = " << bn.getDigits() << std::endl;
	}
	
	// and return the sum of its digits.
	return bn.sumDigits();
}

RegisterSolution(20, solution);

