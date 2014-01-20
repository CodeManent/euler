#ifndef EULER_H
#define EULER_H
#pragma once

#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <iterator>
#include <algorithm>

namespace euler{
/*index
table        loadNumbers(filename)
void         printNumbers(table)

bool         isPrime(n)
vector       primeFactors(n)
vector<pair> mergeFactoers(vector)
T            getNumber(vector<pair>)
vector<pair> leastCommonMultiple(vector<pair>, vector<pair>)
T            countFactors(vector<pair>)
T            countFactors(n)

vector       getProperDivisors(n)

bool         isPalindrome(str)

vector       sieve(n)

table        pascalBox(size)
void         printTable(table)

T            factorial(num)

ostream
	operator<< vector
	operator<< pair
*/

template<typename T>
using line = std::vector<T>;

template<typename T>
using table = std::vector<std::vector<T>>;

/******************************************************************************
 * Loads a file with numbers into a std::vector<std::vector<>>.
 * Each line is loaded in a std::vector and all the std::vectors are being put in another
 * We skip/ignore the empty lines.
 */
template<typename T = long>
table<T> loadNumbers(std::string filename = "numbers.txt"){
	using namespace std;
	table<T> numbers;

	ifstream file(filename.c_str());
	if(!file.is_open())
		throw runtime_error("Couldn't open file");
	
	file.exceptions(ifstream::badbit /* | ifstream::failbit */);

	while(file && !file.eof()){
		string nums;
		//read a line of numbers
		char ch;
		while(file && !file.eof() && (ch = file.get()) != '\n'){
			nums += ch;
		}

		//if the line is empty, continue to the next
		// 1 is for \n
		//also filters out  last empty line
		if(nums.length() <= 1)
			continue;

		//extract the numbers from the line
		istringstream ss(nums);
		line<T> l;
			
		//put numbers in the line
		copy(istream_iterator<T>(ss), istream_iterator<T>(), back_inserter(l));
		//and the line in the table
		numbers.push_back(l);
	}

	if(!file.eof())
		throw runtime_error("Didn't load the whole file");

	return numbers;
}

template<typename T>
void printNumbers(const table<T> &numbers, size_t width = 4, char fill = ' '){
	for(auto line: numbers){
		for(auto number:line)
			std::cout << std::setw(width) << std::setfill(fill) <<  number << " ";
		std::cout << '\n';
	}
}

/******************************************************************************
 * Tests a number whether it is prime. It checks every odd number up to 
 * the square of the parameter if it divides the parameter.
 *
 * The primes are natural numbers so no negatives. 0 and 1 aren't primes.
 * 2 is the only even prime.
 */
template <typename T>
bool isPrime(T n)
{
	if( n < 2 )
		return false;
	if(n == 2)
		return true;
	if(n % 2 == 0)
		return false;

	for(T i = 3; i*i < n; i += 2){
		if(n%i == 0)
			return false;
	}
	return true;
}

/******************************************************************************
 * Returns a std::vector with the prime factors of the number.
 * It goes up from 2 to num and checks every number if it's a factor.
 * Every factor exists in the result as many times as needed to form the num.
 */
template<typename T>
std::vector<T> primeFactors(T n)
{
	std::vector<T> factors;

	if(n == 1)
	{
		factors.push_back(1);
		return factors;
	}
	else if(n  == 0)
	{
		throw std::runtime_error("Can't find the prime factors of 0");
	}

	T i = 2;
	while(i <= n)
	//for(T i = 2; i <= n;)
	{
		if(n % i == 0)
		{
			factors.push_back(i);
			n /= i;
			continue;
		}
		++i;
	}

	return factors;
}

/*
 * Merges a std::vector of factors so that each prime factor appears only once
 * in the result accompanied by its number of appearences (exponent).
 *
 * eg for (2, 2, 5) -> ( (2, 2), (5, 1) )
 */
template<typename T>
std::vector<std::pair<T, T>> mergeFactors(std::vector<T> factors){
	using namespace std;
	vector<pair<T, T>> result;
	if(!is_sorted(factors.begin(), factors.end()))
		sort(factors.begin(), factors.end());
	
	// =0 because 0 cannotbea factor so we force adding the first
	// in the std::vector with exponent(.second) =1
	T currentFactor = 0;
	for(auto factor: factors){
		if(factor != currentFactor){
			currentFactor = factor;
			result.emplace_back(currentFactor, 1);
		}
		else{
			result.back().second++;
		}
	}
	
	return result;
}

/******************************************************************************
 * Gets the number that the list of prime factores stands for
 */
template <typename T>
T getNumber(std::vector<std::pair<T, T>> factors){
	if(factors.size() == 0)
		return 0;

	T result = 1;

	for(auto factor: factors){
		T tempResult = factor.first;

		for(auto i = factor.second -1; i != 0; --i)
			tempResult *= factor.first;

		result *= tempResult;
	}

	return result;
}


template <typename T>
std::vector<std::pair<T, T>> leastCommonMultiple(const std::vector<std::pair<T, T>> &f1,
                                       const std::vector<std::pair<T, T>> &f2)
{
	using namespace std;
	vector<pair<T, T>> result;
	auto i1 = f1.begin();
	auto i2 = f2.begin();

	bool finished = false;
	while(!finished){
		if(i1->first < i2->first)
			result.push_back(*i1++);
		else if(i1->first > i2->first)
			result.push_back(*i2++);
		else if(i1->first == i2->first){
			result.emplace_back(i1->first, max(i1->second, i2->second));
			++i1;
			++i2;
		}
		
		if(i1 == f1.end()){
			copy(i2, f2.end(), back_inserter(result));
			finished = true;
		}
		else if( i2 == f2.end() ){
			copy(i1, f1.end(), back_inserter(result));
			finished = true;
		}
	}

	return result;
}


/******************************************************************************
 * Given the prime factors and their exponents we can find how many factors a
 * number has.
 * it is (e1+1)*(e2+1)*....*(en+1)
 */
template<typename T>
T countFactors(const std::vector<std::pair<T, T>> &pfactors)
{
	T count = 1;
	for(auto f: pfactors)
		count *= f.second + 1;
	
	return count;
}

/*
 * A simple interface for the countFactors function that throws away the
 * computed prime factors and their merged form (factor/exponent). It just
 * returns how many factors a specific number has.
 */
template<typename T>
T countFactors(T number){
	return countFactors(mergeFactors(primeFactors(number)));
}

/******************************************************************************
 * Returns the proper divisors of a number. 
 * (all the numbers < n that divide it)
 */
template <typename T>
std::vector<T> getProperDivisors(T num){
	if(isPrime(num) or (num == 1)){
		return {1};
	}
	
	//get the prime factor of the number
	auto pfactors = primeFactors(num);

	//and add them to the result because they obviously are divisors
	std::set<T> divisors(pfactors.begin(), pfactors.end());

	// from the prime factors, compute all the divisors and add them to the set
	for(const auto &pf: pfactors){
		std::set<T> newDivisors;
		for(const auto &d: divisors){
			if(num%(pf*d) == 0 && pf*d != num){
				newDivisors.insert(pf*d);
			}
		}
		divisors.insert(newDivisors.begin(), newDivisors.end());
	}

	//1 is always a divisor
	divisors.insert(1);


	return std::vector<T>(divisors.begin(), divisors.end());
}


/******************************************************************************
 * Basic straight-forward implementation for palindrome string.
 */
template<class T>
bool isPalindrome(T str){
	auto front = str.begin();
	auto back = str.rbegin();
	for(auto i = str.size(); i > str.size()/2; --i)
		if(*front++ != *back++)
			return false;
	return true;
}

/******************************************************************************
 * Implemenation of the sieve of eratosthenis.
 */
template <typename T>
std::vector<T> sieve(T top){
	std::vector<bool> marks(top+1, true);
	marks[0] = false;
	marks[1] = false;

	// mark out all the non-primes
	for(T i=2; i <= top; ++i){
		if(marks[i]){
			// all non primes below i*i are marked by previous steps
			auto start = i*i;

			if(start > top)
				break;

			//mark all the remaining multiples of i
			for(auto j = start; j <= top; j += i)
				marks[j] = false;
		}
	}

	std::vector<T> result;
	//result.reserve(sqrt(top));

	//collect the primes
	for(T i=2; i <= top; ++i)
		if(marks[i])
			result.push_back(i);
	
	return result;
}

/******************************************************************************
 * Creates a (size X size) table filled with the appropriate pascal triangle
 * values.
 */
template <typename T>
table<T> pascalBox(const size_t size){
	// allocate the table and initialize it with ones.
	table<T> pascalBox(size, line<T>(size, 1));

	// iterate over the diagonals and fill the pascal triangle values.
	for(size_t j = 1; j <size*2; ++j){
		for(size_t i=1; i < j; ++i){
			auto y = j-i;
			auto x = i;
			if(y < size && x < size)
				pascalBox[y][x] = pascalBox[y][x-1] + pascalBox[y-1][x];
		}
	}

	return pascalBox;
}

/******************************************************************************
 * Iterates over the elements of the table and prints its elements on the
 * console.
 */
template <typename T>
void printTable(const table<T> &tbl, bool borders = true){
	// calculate the column sizes.
	line<size_t> len(tbl[0].size(), 0);
	for(auto ln: tbl){
		size_t x = 0;
		for(auto num: ln){
			// the length of the number is 1+log10(number)
			// we add an extra space for separation/readability
			size_t currentLength = num<0 ? 2+log10(-num) : 1+log10(num);
			if(currentLength > len[x])
				len[x] = currentLength;
			if(currentLength > 100){
				std::cout << "currentLength = " << currentLength
				          << " for number " << num;
			}
			++x;
		}
	}

	//preapre line separator
	std::string lineSeparator="\n+";
	if(borders){
		for(auto l : len){
		try{
			std::clog << "Creating string og length " << l << std::endl;
			lineSeparator.append(std::string(l, '-'));
		}
		catch(...){
			std::cerr << "gtp\n";
			throw;
		}
			lineSeparator += "+";
		}
		lineSeparator += "\n";
	}
	
	std::cout << lineSeparator;
	// print the values in the cells
	for(auto ln: tbl){
		size_t x = 0;
		if(borders)
			std::cout << '|';
		for(auto num: ln){
			std::cout << std::setw(len[x++]) << num;
			if(borders)
				std::cout << '|';
		}
		std::cout << lineSeparator;
	}
	return;
}

template<typename T>
T factorial(T num){
	T result = 1;
	for(auto i = num; i > 1; --i)
		result *= i;
	
	return result;
}


// namespace euler end
}

/******************************************************************************
 * Helper operator overload to print the contents of a std::vector.
 * It is put in the global namespace so as to be enabled by default.
 */
template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &cont){
	os << '(';
	for(auto i = cont.begin(); i != cont.end(); ++i){
		os << *i;
		if(i != cont.end()-1)
			os << ", ";
	}

	os << ')';

	return os;
}

/******************************************************************************
 * Helper operator overload to print the contents of a std::pair.
 */
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p){
	os << '(' << p.first << ", " << p.second << ')';
	return os;
}


#endif

