#include "../solutions.h"
#include "../bignum.h"
#include <algorithm>
#include <fstream>

/*
 * Loads the contents of the file into a vector
 * Each line(number) is represented by a string in the vector.
 */
static std::vector<std::string> loadFile(const std::string &path){
	std::ifstream file(path);
	std::vector<std::string> result;
	while(file && !file.eof()){
		std::string tmp;
		file >> tmp;
		result.push_back(tmp);
	}

	return result;
}


static long solution(){
	// load the file containing numbers
	auto numbers = loadFile("problem13/numbers.txt");
	// create the BigNums from the file so we can compute the result
	std::vector<euler::BigNum> bigNumbers;
	for(auto strNum: numbers)
		bigNumbers.emplace_back(strNum);
	
	// add all the begNums togather
	auto acc = std::accumulate(bigNumbers.cbegin(),
	                           bigNumbers.cend(),
							   euler::BigNum("0"));
	// extract the first 10 digits (as requested by the problem
	std::string strNum(acc.getDigits().begin(), acc.getDigits().begin()+10);

	// convert them to a number (long) so we can return them.
	return atol(strNum.c_str());
}

RegisterSolution(13, solution);

