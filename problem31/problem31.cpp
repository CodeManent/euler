#include "../solutions.h"
#include "../euler.h"
#include <iostream>
#include <numeric>

namespace problem31{


unsigned long coins[] = {
	1, 2, 5, 10, 20, 50, 100, 200
};


/*
 * This solution fails because it treats solutions like 2+1 and 1+2 as distinct.
 * It also overflows on the additions.
 *
 * Dynamic programming solution. 
 * We go up from 0 to 200 and find all the possible ways to constrct a value.
*/
long solution()
{
	unsigned long ways[201] = {1};
	unsigned long target = 200;

	for(unsigned long value = 1; value <= target; ++value){
		unsigned long valueWays = 0;
		for(auto coin: coins){
			if(value >= coin){
				auto value2 = value - coin;
				//valueWays++;
				valueWays += ways[value2];
			}
		}
		ways[value] = valueWays;
	}
/*
	for(size_t i = 0; i <= 200; ++i){
		std::cout << i << ":\t" << ways[i] << std::endl;
	}
// */
	return ways[200];
}

// Dont register a wrong "solution".
// RegisterSolution(31, solution);


///////////////////////////////////////////////////////////////////////////////

/*
 * Dynamic programming solution.
 */
long solution2(){
	unsigned long ways[201] = {1};
	unsigned long target = 200;

	for(auto coin: coins){
		for(unsigned long value = 1; value <= target; ++value){
			if(value >= coin)
				ways[value] += ways[value - coin];
		}
	}

	/*
	unsigned value = 0;
	for(auto valueWays: ways)
		std::cout << value++ << ": \t" << valueWays << std::endl;
	// */

	return ways[200];
}

RegisterSolution(31, solution2);

}

