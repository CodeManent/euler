#include "results.h"
#include <exception>

std::map<unsigned int, long> results = {
	{1, 233168},
	{2, 4613732},
	{3, 6857},
	{4, 906609},
	{5, 232792560},
	{6, 25164150},
	{7, 104743},
	{8, 40824},
	{9, 31875000},
	{10, 142913828922},
	{11, 70600674},
	{12, 76576500},
	{13, 5537376230},
	{14, 837799},
	{15, 137846528820},
	{16, 1366},
	{17, 21124},
	{18, 1074},
	{19, 171},
	{20, 648},
	{21, 31626},
	{22, 871198282},
	{23, 4179871},
	{24, 2783915460},
	{25, 4782},

	{27, -59231},
	{28, 669171001},
	{29, 9183},
	{30, 443839},
	{31, 73682},
	{32, 45228},

	{48, 9110846700},

	{67, 7273}
};

RESULT_STATUS checkResult(unsigned int problemNo, long result){
	try{
		auto localResult = results.at(problemNo);
		return localResult == result ? RESULT_GOOD : RESULT_BAD;
	}
	catch(const std::out_of_range &){
		return NO_RESULT;
	}
}


