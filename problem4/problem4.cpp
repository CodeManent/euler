#include "../solutions.h"
#include "../euler.h"

/******************************************************************************
 * Interface method for the isPalindrome(string).
 * Converts the long to a string and calls the method above to check whether
 * the generated string is a palindrome one.
 */
static bool isPalindrome(long num){
	std::ostringstream oss;
	oss << num;
	auto str = oss.str();
	return euler::isPalindrome(str);
}


/*
 * Scans all the number pairs from 100 up to 999 and checks if their
 * multiplication generates a palindrome number.
 * The found palindromes are checked against the currently found one and if it
 * is bgger, we keep it as the new result.
 */
static long solution(){
	long maxPalindrome = 0;
//	long maxI, maxJ;

	for(long i = 100; i < 1000; ++i)
		for(long j = 100; j < 1000; ++j)
			if(maxPalindrome < i*j)
				if(isPalindrome(i*j))
					maxPalindrome = i*j;

	return maxPalindrome;
}

RegisterSolution(4, solution);

