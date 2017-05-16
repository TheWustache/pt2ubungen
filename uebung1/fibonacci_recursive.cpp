
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits.h>

// golden ratio
double phi = 1.6180339887498948482;

// global max value for number so it only has to be calculated once
// see http://en.wikipedia.org/wiki/Fibinochi_numbers#Relation_to_the_golden_ratio (03.05.17)
const int numberMax = std::log((long int)INT_MAX * sqrt(5)) / std::log(phi) + 0.5;

static long steps = 0;

int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps
    steps += 1;

	// ToDo: Exercise 2.a - return 0 on bad arguments
    
    if(number <= 0 || number > numberMax) {
        return 0;
    }

	// ToDo: Exercise 2.a - retrieve nth fibonacci number recursively
    
    // seed values
    if(number <= 2) {
        return 1;
    }
    
	return fibonacci(number-1) + fibonacci(number-2);
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	// ToDo: Exercise 2.c - print calculation steps

    std::cout << n << " : " << fibonacci(n) << " : #" << steps << std::endl;

	return 0;
}
