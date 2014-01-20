#include "../euler.h"
#include "../solutions.h"
#include "../stream.h"
#include <algorithm>

/******************************************************************************
 * Finds the max factor of the given number.
 * First it gets all its factors and then scans them to find the max.
 */
static long solution1(){
	long num = 600851475143L;
	auto f = euler::primeFactors(num);

	//for(auto n: f)
	//	std::cout << n << ", ";
	using namespace euler;

	auto maxFactor = std::max_element(f.begin(), f.end());
	return *maxFactor;
}
RegisterSolution(3, solution1);





/******************************************************************************
 * The second solution uses the same method to find the solution with the
 * difference that it is implemented around number streams.
 */
static long solution2(){
	long num = 600851475143L;

	euler::PrimeFactorStream pfs(num);
	long maxFactor = 0;
	for(; !pfs.isEmpty(); pfs.next()){
		if(maxFactor < *pfs)
			maxFactor = *pfs;
		//std::cout << *pfs << ", ";
	}

	return maxFactor;
}

RegisterSolution(3, solution2);

