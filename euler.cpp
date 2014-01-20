#include <iostream>
#include <cstdlib>
#include "solutions.h"
#include "results.h"
#include <thread>
#include <stdexcept>
#include <future>

// definition of the static map containing the solutions
// The solutions are registered by their translation units/object
// files by exploiting static initialization.
//std::map<int,std::pair<solutionFunc, int> >
solutionsContainer&
getSolutions(){
	static solutionsContainer solutions;

	return solutions;
}

static void sequentialSolutions();
static void parallelSolutions();
static long threadFunc(const std::pair<unsigned int, solutionFunc> s);
static void printResult(unsigned int, long);
static void paralleSolutionsSequentialResults();

/******************************************************************************
 * program entry point
 */
int main(int /* argc */ , char** /* argv */){
	std::cout << "Project euler!" << std::endl;
	

	if(false)
		sequentialSolutions();
	else if(false)
		parallelSolutions();
	else if(true)
		paralleSolutionsSequentialResults();
	else
	{
		std::cerr << "No solution computation method used" << std::endl;
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}

/******************************************************************************
 *
 */
static void sequentialSolutions()
{
	for(const auto t: getSolutions()){
		// the result contains what the funcion returns, which is compared
		// with the correct/expected value. A message is printed on error.
		const auto problemNo = t.first;
		const auto result = t.second();
//		const auto correct = t.second.second;
		
		std::cout << "Problem " << problemNo << ": " << result;
		switch(checkResult(problemNo, result)){
		case RESULT_GOOD:
			break;
		case RESULT_BAD:
			std::cout << " (incorrect)";
			break;
		case NO_RESULT:
			std::cout << " (untested)";
			break;
		default:
			std::cout << " unknown result status";
		}

		std::cout << std::endl;
	}
}

/******************************************************************************
 *
 */
static void parallelSolutions()
{
	std::vector<std::thread> threads;
	//create the threads to compute the solutions.
	for(const auto s: getSolutions())
	{
		try
		{
			threads.emplace_back(&threadFunc, s);
		}
		catch(const std::system_error &exp)
		{
			std::cout << "Thread creation excepion for problem " << s.first 
			<< ": " << exp.what() << std::endl;
		}
	}


	// Wait for thethreads to finish.
	for(auto &t: threads)
		t.join();
}

/******************************************************************************
 * One task/thread per solution. Results are printed by main
 * after all of them have been computed.
 */
static void paralleSolutionsSequentialResults()
{

	//Create the containers to use and preallocate the memory needed
	auto scount = getSolutions().size();
	//one thread for each solution for now
	std::vector<std::thread> threads;
	threads.reserve(scount);
	//one future for each solution
	std::vector<std::future<long>> futures;
	futures.reserve(scount);

	// Grab the futures and create a thread for each solution;
	for(const auto &s : getSolutions() ){
		// get the function pointer for the solution
		auto fp = s.second;
		// and create a future and a thread for it through a prepared_task.
		std::packaged_task<long()> tsk(fp);
		futures.emplace_back(std::move(tsk.get_future()));
		threads.emplace_back(std::move(tsk));
	}

	// wait for the threads t finish the computations.
	for(auto &t: threads)
		t.join();

	// print the computed results (and compared them to the expected ones).
	for(size_t i=0; i < getSolutions().size(); ++i){
		const auto problem = getSolutions().at(i).first;
		long result = futures[i].get();

		printResult(problem, result);
	}
}

/******************************************************************************
 * It prints the result to the console as well as its satus.
 */
void printResult(unsigned int problemNo, long result){
		std::cout << "Problem " << problemNo << ": " << result;
		switch(checkResult(problemNo, result)){
		case RESULT_GOOD:
			break;
		case RESULT_BAD:
			std::cout << " (incorrect)";
			break;
		case NO_RESULT:
			std::cout << " (untested)";
			break;
		default:
			std::cout << " unknown result status";
		}

		std::cout << std::endl;
}


/******************************************************************************
 * The function that is used by the threads created in main.
 */
static long threadFunc(const std::pair<unsigned int, solutionFunc> s){
	const auto result = s.second();
	printResult(s.first, result);

	return EXIT_SUCCESS;
}

