#ifndef SOLUTIONS_H
#define SOLUTIONS_H


#include <map>
#include <utility>
#include <vector>

// typedef for the solution function prototype
typedef long(*solutionFunc)(void);

// typedef for the solutions container type for less typing and easier code
typedef std::vector<std::pair<long, solutionFunc>>
solutionsContainer;

// returns the static container for the solutions
solutionsContainer& getSolutions();

// Helping tsruct to register solutions at the beginnig of the program
// before main
struct SolutionRegistrar{
	SolutionRegistrar(int num, solutionFunc func){
		getSolutions().emplace_back(num, func);
		delete this;
	}
};

// make it a static pointer and delete this in the constructor after registering
// (i think that) allows us to register the solutions without reserving exess
// memory (instead possibly of one pointer per solution).
#define RegisterSolution(num, func) \
static  auto _SolutionRegistrarObject_##num_##func = new SolutionRegistrar(num, func)

#endif
