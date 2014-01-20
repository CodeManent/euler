#include "../solutions.h"
#include "../euler.h"

static long primesProduced(const long a, const long b)
{
	long n = 0;

	auto f = [a, b](long n) {return n*n + a*n + b;};
	
	for(n = 0; euler::isPrime(f(n)); ++n)
		;

	return n;
}

static long solution()
{
	long maxA = 0, maxB = 0, maxCount = -1;

	for(long a = -1000; a < 1001; ++a){
		for(long b = a /* -1000 */; b < 1001; ++b){
			auto count = primesProduced(a, b);
			if(count > maxCount){
				maxCount = count;
				maxA = a;
				maxB = b;
			}
		}
	}

	return maxA*maxB;
}

RegisterSolution(27, solution);

