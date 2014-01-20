#include "../solutions.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <unordered_map>

/*
 * We use a map to storethe computed nodes of the collaz graph. Each entry is
 * comprised of the node number (as key) and the node length.
 */
static
std::unordered_map<long, long> collaz;


static
void prepareCollaz(){
	collaz[0] = 0;
	collaz[1] = 1;

	std::stack<long> st;
	for(long start = 2; start < 1000000; ++start){
		auto i = start;
		auto pos = collaz.find(start);

		while((pos = collaz.find(i)) == collaz.end()){
			st.push(i);
			long next = i%2 == 0 ? i/2 : 3*i+1;
			i = next;
		}


		long length = pos->second;

		while(!st.empty()){
			collaz[st.top()] = ++length;
			st.pop();
		}
	}
}

static
long getMaxChain(){
	long longestChain = 0;
	long maxLength = 0;
	for(long i = 2; i< 1000000; ++i){
		if(maxLength < collaz[i]){
			maxLength = collaz[i];
			longestChain = i;
		}
	}

	return longestChain;
}
		
static
long solution(){
	prepareCollaz();
	
	return getMaxChain();
}

RegisterSolution(14, solution);


/******************************************************************************
 * 2nd solution to the 14th problem.
 * We walk through each chain and find the chain with the maximum length.
 */
static
long solution2(){
	long maxLength = 0;
	long maxChain = 0;

	for(long i = 2; i < 1000000; ++i){
		long current = i;
		long length = 0;
		while(current != 1){
			long next = current % 2 == 0 ? current/2 : current*3+1;
			++length;
			current = next;
		}

		if( length > maxLength){
			maxLength = length;
			maxChain = i;
		}
	}

	return maxChain;
}

RegisterSolution(14, solution2);

