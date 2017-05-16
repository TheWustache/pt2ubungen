
#include <cstdlib>
#include <iostream>


// ToDo: Exercise 2.d - adapt and implement combinations

unsigned long long combinations(int number)
{
    if(number == 1) {
        return 1;
    }
    if(number == 2) {
        return 2;
    }
    
    unsigned long long prevCombs = 1;
    unsigned long long prevPrevCombs;
    unsigned long long combs = 2;
    
    for(int i = 0; i < number-2; i++) {
        // update prevfib values
        prevPrevCombs = prevCombs;
        prevCombs = combs;
        // calculate next fub
        combs = prevCombs + prevPrevCombs;
    }
    
    return combs;
}


int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

    std::cout << combinations(n) << std::endl;

	return 0;
}
