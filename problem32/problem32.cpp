#include "../solutions.h"
#include "../euler.h"

#include <set>
//#include <iostream>

namespace euler{
	namespace problem32{
// Problem description:
// Find the sum of all products whose multiplicand/multiplier/product
// identity can be written as a 1 through 9 pandigital.

/* Checks whether the passed number is pandigital.
 */
bool isPandigital(long num){
	char freq[10] = {0};

	while(num > 0){
		long next = num/10;
		auto last_digit = num % 10;

		if(last_digit == 0 or freq[last_digit] == 1){
			return false;
		}
		++freq[last_digit];
		num = next;
	}
	int sum = 0;
	for(const auto f: freq){
		sum += f;
	}
	return sum == 9;
}

/* Returns a number that has all the digits (base 10) of the two parameters.
 */
long conatenateNumbers(long num1, long num2)
{
	const auto temp = num1;

	while(num1 > 0){
		num1 /= 10;
		num2 *= 10;
	}
	return num2 + temp;
}

/* Implementation of a brute force algorithm. The ifs reduce radically the search space.
 */
long solution(){
	std::set<long> products;
	for(long i=1; i < 10000L; ++i){
		for(auto j=i+1; j<10000L; ++j){
			auto prod = i*j;

			auto full_number = conatenateNumbers(i, j);
			full_number = conatenateNumbers(full_number, prod);

			if(full_number < 123456789L){
				continue;
			}
			if(987654321L < full_number){
				break;
			}

			if(isPandigital(full_number)){
				products.insert(prod);
				// Uncommenting the following line prints the products at runtime.
				// std::cout << i << " * " << j << " = " << prod << "\n";
			}
		}
	}

	return std::accumulate(products.cbegin(), products.cend(), 0L);
}

RegisterSolution(32, solution);

	}
}

