#include "../solutions.h"
#include "../euler.h"
#include <algorithm>

/*
 * Calculates the least common multiple of the numbers 1-20
 */
static long solution(){
	std::vector<long> numbers(20, 0);
	std::iota(numbers.begin(), numbers.end(), 1);

	using namespace euler;

	auto result = mergeFactors(primeFactors(numbers.front()));
	for(auto number: numbers){
		const auto primesList = mergeFactors(primeFactors(number));
		result = leastCommonMultiple(result, primesList);
	}

	return getNumber(result);
}

RegisterSolution(5, solution);

