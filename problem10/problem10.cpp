#include "../solutions.h"
#include "../euler.h"
#include <algorithm>

namespace euler{
	namespace problem10{

/*
 * By using the sieve of eratosthenis, we find all the primes that are
 * < 2000000 and just sum them
 */
long solution(){
	auto primes = sieve(2000000L);

	auto result = std::accumulate(primes.begin(), primes.end(), 0L);

	return result;
}

RegisterSolution(10, solution);

	} // problem10
} // euler

