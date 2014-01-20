#include "../solutions.h"
#include <cmath>
#include <algorithm>
#include <vector>

/*
 * Instead of checking every smaller prime, we just check the primes up 
 * to sqrt(number). The memory contains every prime up to num-1.
 */
static bool isPrime(long number, std::vector<long> &memory){
	long sq = sqrt(number);
	auto pos = std::find_if(memory.begin(), memory.end(), [sq](long num){
		return num > sq;
	});

	for(; pos != memory.begin(); --pos)
		if(number % *pos == 0)
			return false;
	
	return true;
}


static long solution(){
	std::vector<long> primes;
	primes.push_back(2);

	for(long num = 3; primes.size() < 10001; num += 2)
		if(isPrime(num, primes))
			primes.push_back(num);
	
	//now at the end of the vector will be the prime we want
	return primes.back();
}

RegisterSolution(7, solution);

