#include "../solutions.h"
#include "../euler.h"
#include <algorithm>

/*
 * We compute only 4 of hte 8 available progucts.
 * The directions we compute are:
 *     - Right
 *     - Down/Right
 *     - Down
 *     - Down/Left
 *
 *The remainig products don't need to be calculated.
 */
template<typename C, typename T>
static T maxProductAt(C y, C x, const euler::table<T> &numbers){
	C factors = 4;

	// product on the horizontal line
	T prod1 =1;
	if(x+factors < numbers.size())
		for(C i = 0; i < factors; ++i)
			prod1 *= numbers[y][x+i];
	
	// product on the diagonal line
	T prod2 = 1;
	if(x+factors < numbers.size() && y+factors < numbers.size())
		for(C i = 0; i < factors; ++i)
			prod2 *= numbers[y+i][x+i];
	
	// product on the vertical line
	T prod3 = 1;
	if(y+factors < numbers.size())
		for(C i = 0; i < factors; ++i)
			prod3 *= numbers[y+i][x];
	
	// the down-left diagonal line products
	T prod4 = 1;
	if(y+factors < numbers.size() && x>=factors)
		for(C i = 0; i < factors; ++i)
			prod4 *= numbers[y+i][x-i];
	
	//get the maximum of the computed products
	return std::max({prod1, prod2, prod3, prod4});
}

/*
 * We traverse the table positions, calculating the product that corresponds to
 * each position. The maximum of the products is the desired one.
 */
static
long solution(){
	typedef long  numberType;
	auto nums = euler::loadNumbers<numberType>("problem11/numbers.txt");
	numberType  maxProduct = 0;

	for(size_t y = 0; y < nums.size(); ++y)
		for(size_t x = 0; x < nums[y].size(); ++x)
			maxProduct = std::max(maxProduct, maxProductAt(y, x, nums));

	return maxProduct;
}

RegisterSolution(11, solution);

