#ifndef EULER_RESULTS_H
#define EULER_RESULTS_H

#include <map>
extern std::map<unsigned int, long> results;

enum RESULT_STATUS{
	RESULT_GOOD,
	RESULT_BAD,
	NO_RESULT
};

RESULT_STATUS checkResult(unsigned int problemNo, long result);

#endif

