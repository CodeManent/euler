#include "../solutions.h"
#include "../euler.h"
#include <iterator>
#include <string>
#include <algorithm>

namespace euler{
	namespace problem22{

/******************************************************************************
 * Loads the contents of a file into a string
 */
std::string loadFile(const std::string &path)
{
	std::string result;
	std::ifstream f(path);
	f.exceptions(std::ios_base::badbit | std::ios_base::failbit);

	std::copy(std::istreambuf_iterator<char>(f),
	          std::istreambuf_iterator<char>(),
			  std::back_inserter(result));

	return result;
}

/******************************************************************************
 * Parses the string to extract the names.
 * The format is "NAME" with , beign used as name separator.
 */
std::vector<std::string> parseNames(const std::string &str)
{
	std::vector<std::string> result;

	for(auto p = str.begin(); p != str.end(); ++p)
	{
		if(*p == '"')
		{
			// get the name and add it onto the result

			auto name_start = p+1;
			auto name_end = name_start + 1;
			//find the closing tag for the name
			while(*++name_end != '"');
			// store name (without the ")
			result.emplace_back(name_start, name_end);

			// set iterator at the end of the name
			p = name_end;
		}
		else if( *p == ',')
		{
			// consume and ignore name separator
		}
		else{
			throw std::runtime_error(std::string("Unexpected character: ") + *p);
		}
	}

	return result;
}

long charValue(const char &ch)
{
	return ch - 'A' + 1;
}

long nameValue(const std::string &name)
{
	long result = 0;
	for(auto ch: name)
		result += charValue(ch);
	
	return result;
}

long nameScore(const size_t position, const std::string &name)
{
	return position * nameValue(name);
}

long solution()
{
	long result = 0;
	auto names = parseNames(loadFile("problem22/names.txt"));
	std::sort(names.begin(), names.end());

	for(size_t pos = 0; pos < names.size(); ++pos)
		//+1 because 0-based array
		result += nameScore(pos+1, names.at(pos));
	
	return result;
}

RegisterSolution(22, solution);

	} // problem22
} // euler

