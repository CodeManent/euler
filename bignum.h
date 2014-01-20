#ifndef EULER_BINGUM_H
#define EULER_BINGUM_H

#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace euler{

class BigNum{
	std::string digits;
public:
	BigNum(std::string strnum = "")
	:digits(strnum)
	{
	}

	BigNum(long num)
	:digits(itoa(num))
	{
	}

	~BigNum(){
	}

	std::string itoa(const long num)
	{
		std::ostringstream ss;

		ss << num;

		return ss.str();
	}

	bool operator==(const BigNum& rhs)
	{
		return digits == rhs.digits;
	}

	BigNum operator+(const BigNum& n2)const{
		// preallocate some space for the result
		BigNum result;
		result.digits.reserve(std::max(digits.length(), n2.digits.length()) +1);

		// the iterators for each number's digits
		// p1 the bigger (in digits) number
		// p2 the smaller
		auto p1 = digits.crbegin();
		auto e1 = digits.crend();

		auto p2 = n2.digits.crbegin();
		auto e2 = n2.digits.crend();

		bool carry = false;

		if(digits.length() < n2.digits.length()){
			p1 = n2.digits.crbegin();
			e1 = n2.digits.crend();

			p2 = digits.crbegin();
			e2 = digits.crend();

		}
		
		auto addDigit = [](const char d1, const char d2, bool carry) -> std::pair<const char, bool> {
			const char n1 = d1 - '0';
			const char n2 = d2 - '0';
			auto result = n1 + n2 + carry;
			
			if(result > 9){
				result -=10;
				carry = true;
			}
			else{
				carry = false;
			}

			return std::make_pair(result+'0', carry);
		};

		//we go on ultil we exhaust the smaller number
		for( ; p2 != e2; ++p1, ++p2){
			auto tmp = addDigit(*p1, *p2, carry);
			result.digits.push_back(tmp.first);
			carry = tmp.second;
		}

		//ge go on untilew exhaust the bigger number
		for(; p1 != e1; ++p1){
			auto tmp = addDigit(*p1, '0', carry);
			result.digits.push_back(tmp.first);
			carry = tmp.second;
		}

		//if at the end there is still a carry, we add 1in the front
		if(carry)
			result.digits.push_back('1');

		std::reverse(result.digits.begin(), result.digits.end());
		return result;
	}
	
	/*
	 * Crude multiply function by continiously adding the same number.
	 */
	template<typename T>
	BigNum operator*(T rhs){
		if(rhs == 0)
			return BigNum("0");

		BigNum result = *this;
		for(decltype(rhs) i(1); i < rhs; ++i)
			result = result + *this;

		return result;
	}

/*
	BigNum pow(const long exp)
	{
		if(exp == 0)
		{
			if(*this == 0)
				throw std::runtime_error("0 on the power of 0");

			return BigNum(1);
		}

		BigNum result = 1;
		for(long e = 0; e < exp; ++e)
		{
			result = result * (*this);
		}

		return result;
	}
*/

	const std::string& getDigits()const{
		return digits;
	}

	long sumDigits() const{
		long result = 0;
		for(auto d : digits)
			result += d - '0';

		return result;
	}

	size_t countDigits(){
		return digits.length();
	}
};

//closing namespace euler
}

#endif

