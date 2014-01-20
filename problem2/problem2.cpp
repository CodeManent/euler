#include "../solutions.h"
#include "../stream.h"

static long solution(){
	long result = 0;
	//Create a fibonacci number stream...
	euler::FibonacciStream fs(1, 1);

	// and keep only the even ones that are smaller than 4000000.
	for(euler::EvenFilter ef2(&fs); *ef2 < 4000000; ef2.next())
	{
		//std::cout << *ef2 << ", ";
		//add those numbers to form the result.
		result += *ef2;
	}

	return result;
}

RegisterSolution(2, solution);
