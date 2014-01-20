#include "../solutions.h"
#include "../euler.h"
#include <algorithm>
#include <iostream>

/*
 * By using the sieve of eratosthenis, we find all the primes that are
 * < 2000000 and just sum them
 */
static long solution(){
	auto primes = euler::sieve(2000000L);

	auto result = std::accumulate(primes.begin(), primes.end(), 0L);

	return result;
}

RegisterSolution(10, solution);

