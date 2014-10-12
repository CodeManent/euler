#include "../solutions.h"
#include "../bignum.h"

namespace euler{
	namespace problem25{

/*
 * Returns which fibonacci number has more than 1000 digits.
 */
long solution(){
	BigNum f1("1");
	auto f2 = f1;
	long term = 2;
	do{
		auto f = f1 + f2;
		f2 = f1;
		f1 = f;
		++term;
	} while(f1.countDigits() < 1000);

	return term;
}

RegisterSolution(25, solution);

	} // problem25
} // euler

