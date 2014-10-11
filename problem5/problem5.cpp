#include "../solutions.h"
#include "../euler.h"
#include <algorithm>

namespace euler{
	namespace problem5{

/*
 * Calculates the least common multiple of the numbers 1-20
 */
long solution(){
	std::vector<long> numbers(20, 0);
	std::iota(numbers.begin(), numbers.end(), 1);

	auto result = mergeFactors(primeFactors(numbers.front()));
	for(auto number: numbers){
		const auto primesList = mergeFactors(primeFactors(number));
		result = leastCommonMultiple(result, primesList);
	}

	return getNumber(result);
}

RegisterSolution(5, solution);

	} //problem5
} //euler

