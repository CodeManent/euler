#include "../solutions.h"
#include "../bignum.h"
#include <iostream>

/*
 * Self powers
 *
 * Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000
 *
 * For every multiplication and addition, we keep only the last 10 digits. The
 * most significant digits aren't part of the result and dont't affect the
 * solution.
 */
namespace problem48{

unsigned long filter(unsigned long num){
	return num % 10000000000UL;
}

unsigned long ppow(unsigned long num){
	unsigned long result = num;
	for(unsigned long i = 1; i < num; ++i){
		result = filter(result*num);
	}

	return result;
}

long solution(){
	unsigned long result = 0;
	for(unsigned long i = 1; i < 1001; ++i){
		result = filter(result + ppow(i));
	}
	return result;
}

RegisterSolution(48, solution);
}


