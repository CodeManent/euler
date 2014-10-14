#include "../solutions.h"
#include "../euler.h"
#include <set>

namespace euler{
	namespace problem29{

/******************************************************************************
 * Counts the distinct values of a^b wita 2<=a,b<=100.
 *
 * We don't actually compute the values.
 * We find the prime factors of the base (a) and then multiply each of its
 * exponents with b. The result (if computed equals to the number needed). This
 * way we avoid the computation that overflows. We keep only the distinct terms
 * with the help of a set.
 */
long solution()
{
	// the set which holds the unique terms
	std::set<std::vector<std::pair<long, long>>> terms;

	for(long base = 2; base <= 100; ++base){
		// get the prime factorization of the base
		const auto b = mergeFactors(primeFactors(base));
		for(long exp = 2; exp <= 100; ++exp){
			auto b2 = b;
			for(auto &pair: b2)
				//increase the exponent of each factor
				pair.second *= exp;

			// and store the "computed" number in the set
			terms.insert(b2);
		}
	}

	/* Debugging output
	for(auto & t: terms)
		std::cout << t << " = " <<  getNumber(t) << '\n';
	// */

	// the result is the number of the distinct vaues. The set keps only one
	// copy of each number, so its size is the number we want.
	return terms.size();
}

RegisterSolution(29, solution);

	} // problem29
} // euler

