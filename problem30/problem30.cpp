#include "../solutions.h"
#include "../euler.h"

namespace euler{
	namespace problem30{

// With this functinon we find the upper bound for the computation.
unsigned long findUpperBound(){
	constexpr long _95 = 9*9*9*9*9;
	unsigned long number = 9;
	unsigned long length = 1;
	do{
		++length;
		number = number * 10 + 9;
	}while( number <= length * _95);

	return length * _95;
}

constexpr unsigned long fifthPower[10] = {
	0,
	1,
	2*2*2*2*2,
	3*3*3*3*3,
	4*4*4*4*4,
	5*5*5*5*5,
	6*6*6*6*6,
	7*7*7*7*7,
	8*8*8*8*8,
	9*9*9*9*9
};

constexpr unsigned long sumPowerDigits(unsigned long num){

/*	unsigned long sum = 0;
	while(num > 0){
		sum += fifthPower[num % 10];
		num /= 10;
	}

	return sum;
*/
	// every iteration consumes one digit and returnes the sum of it
	// in the fifth power with the rest of the digits.
	return num > 0 ? fifthPower[num%10] + sumPowerDigits(num/10) : 0;
}


long solution()
{

	auto upperBound = findUpperBound();
	unsigned long sum = 0;

	for(unsigned long num = 10; num <= upperBound; ++num){
		if(sumPowerDigits(num) == num){
			sum += num;
		}
	}

	return sum;
}

RegisterSolution(30, solution);

	} // problem30
} // euler

