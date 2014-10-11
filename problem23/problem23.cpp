#include "../solutions.h"
#include "../euler.h"
#include <vector>
#include <numeric> // accumulate
#include <bitset>

namespace euler{
	namespace problem23{

using namespace std;

enum fixName{ABUDANT, DEFICIENT, PERFECT};

fixName categorize(unsigned long num){
	auto d = getProperDivisors(num);
	auto sum = accumulate(begin(d), end(d), 0UL);

	if(sum == num)
		return PERFECT;
	else if(sum < num)
		return DEFICIENT;
	else
		return ABUDANT;
}

/*
 * Finds the sum of all the positive integers which cannot be written as the
 * sum of two abundant numbers
 */
long solution(){
	constexpr unsigned long range = 28124;

	//find abudant numbers
	bitset<range> abudant;
	for(unsigned long i = 1; i < range; ++i)
		if(categorize(i) == ABUDANT)
			abudant.set(i);

	bitset<range> sumOfAbudant;

	//cross out sums of abudanr numbers
	for(unsigned long i = 1; i < range; ++i){
		if(!abudant.test(i))
			continue;
		for(unsigned long j = i; j < range; ++j){
			if(!abudant.test(j))
				continue;
			if((i+j) < range)
				sumOfAbudant.set(i+j);
		}
	}
	
	// compute the result 
	unsigned long result = 0;
	for(size_t i = 1; i < range; ++i)
		if(sumOfAbudant.test(i) == false)
			result += i;
	
	return result;
}

RegisterSolution(23, solution);

	} // problem23
} //euler

