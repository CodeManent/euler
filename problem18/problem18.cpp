#include "../euler.h"
#include "../solutions.h"
#include <algorithm>

namespace euler{
	namespace problem18{

/* We go from top to bottom row by row and for each element of a row we add it
 * with the max of the two corresponding elements of the previous row. That way,
 * the last row will hold the best sum. Currently we don't keep the best path,
 * only the best result.
 */
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

long solution(){
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

	} // problem18
} // euler

