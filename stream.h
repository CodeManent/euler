#ifndef EULER_STREAM_H
#define EULER_STREAM_H
#pragma once

namespace euler{

/******************************************************************************
 * The interface of a stream of a series of numbers.
 */
class Stream{
	bool empty;
public:
	Stream():empty(false){}
	virtual long  next() = 0;
	virtual long operator*() = 0;
	virtual bool isEmpty(){
		return empty;
	}
	virtual void setEmpty(bool value){
		empty = value;
	}
};

/******************************************************************************
 * A number stream that comprises of the fibonnachi numbers.
 */
class FibonacciStream: public Stream{
	long prev1;
	long prev2;

public:
	FibonacciStream(long prev1, long prev2)
		:prev1(prev1),
		prev2(prev2)
	{
	}
	
	virtual long next(){
		long next = prev1 + prev2;
		prev2 = prev1;
		prev1 = next;
		return next;
	}

	virtual long operator*() {
		return prev1;
	}
};

/******************************************************************************
 * A stream of numbers that comprises of the prime factors of the number given
 * in the constructor.
 */
class PrimeFactorStream: public Stream{
	long num;
	long i;

public:
	PrimeFactorStream(long num)
		:num(num),
		i(2)
	{
		next();
	}

	virtual long next(){
		for(; i <= num; ++i){
			if(num % i == 0){
				num /= i;
				return i;
			}
		}

		setEmpty(true);
		return -1;

	}

	virtual long operator*(){
		return i;
	}
};



/******************************************************************************
 * A stream filter that discards the odd numbers.
 */
class EvenFilter: public Stream{
	Stream *const source;
public:
	// StreamFilter constructor. progresses the values until a valid one is
	// found.
	EvenFilter(Stream *const src)
		:source(src)
	{
		if(source->operator*() % 2 != 0)
			next();
	}
	
	// Finds the next number in the stream that is an Even number.
	virtual long next(){
		long result=0;
		do{
			result = source->next();
		}while(result % 2 != 0);
		return this->operator*();
	}
	
	// Returns the current number of the stream.
	virtual long operator*(){
		return source->operator*();
	}
};

// end of namespace euler
}

#endif

