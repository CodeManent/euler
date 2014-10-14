#include "../euler.h"
#include "../solutions.h"
#include <algorithm>

namespace euler{
	namespace problem67{

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

static long solution(){
	long result = 0;

	auto t = loadNumbers<long>("problem67/triangle.txt");
	compute(t);

	//the number we want is the max of the last line
	result = *std::max_element(t.back().begin(), t.back().end());


	return result;
}

RegisterSolution(67, solution);

	} // problem67
} // euler

