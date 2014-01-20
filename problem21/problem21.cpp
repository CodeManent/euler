#include "../solutions.h"
#include "../euler.h"
#include <vector>
#include <numeric> // accumulate
#include <bitset>

using namespace std;
using namespace euler;

template<typename T>
static T vectorSum(const vector<T> &v){
	return accumulate(begin(v), end(v), T(0));
}

/*
 * Find the sum of all amicable numbers < 10000.
 */
static long solution(){
	constexpr unsigned long range = 10000UL;
	vector<long> amicable;
	bitset<range> checked; // use the bitset to avoid some computations.

	for(unsigned long n=1UL; n < range; ++n){
		if(checked.test(n)){
			// check if we have already considered the current number
			continue;
		}

		auto a = n;
		auto da = vectorSum(getProperDivisors(a));
		auto b = da;

		checked.set(a);

		if(b >= range)
			continue;
		checked.set(b);

		if(b <= a){
			// the two numbers must not be equal to form an amicable pair
			// if < a then we have already checked that number
			// so there is no need to compute divisors and sum of b
			continue;
		}

		auto db = vectorSum(getProperDivisors(b));

		if(a == db){
			amicable.push_back(a);
			amicable.push_back(b);
		}
	}


	return vectorSum(amicable);
}

RegisterSolution(21, solution);

