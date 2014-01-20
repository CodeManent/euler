#include "../euler.h"
#include "../solutions.h"
#include <algorithm>

template<typename T>
void compute(euler::table<T> &table){
	for(size_t y = 1; y < table.size(); ++y){
		for(size_t x = 0; x < table[y].size(); ++x){
			if(x ==  0)
				table[y][x] += table[y-1][x];
			else if(x == table[y-1].size())
				table[y][x] += table[y-1][x-1];
			else
				table[y][x] += std::max(table[y-1][x], table[y-1][x-1]);
		}
	}
}

// We make the func private so we won't have problem with the func name on other
// translation units during the link phase. We just need the function pointer
// that we register at the end.
static long solution(){
	long result = 0;

	auto t = euler::loadNumbers<long>("problem18/numbers.txt");
	//printNumbers(t);
	compute(t);
	//printNumbers(t);

	//the number we want is the max of the last line
	result = *std::max_element(t.back().begin(), t.back().end());


	return result;
}

// Register the solution
RegisterSolution(18, solution);

