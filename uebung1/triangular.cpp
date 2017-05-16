
#include <cstdlib>
#include <iostream>
#include <limits.h>
#include <cmath>
#include <string.h>


int triangular(int number)
{
    if(number <= 1)
        return 1;
    
	return triangular(number - 1) + number;
}

void pretty_print(int decimal)
{
	// ToDo: Exercise 1.c - print number with decimal marks to console
    
    std::string outs = "";
    
    while(decimal > 0) {
        outs = std::to_string(decimal % 1000) + outs;
        decimal /= 1000;
        if(decimal > 0) {
            outs = "." + outs;
        }
    }
    
    std::cout << outs;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	// ToDo: Exercise 1.c - print all numbers with decimal marks

	// ToDo: Exercise 1.b - check if n is in domain, if not print valid domain and codomain and return 2
    int dmax = -0.5 + sqrt(0.25 + 2 * (long int)INT_MAX);
    
    if(n > dmax || n <= 0) {
        std::cout << "domain = [1;" << dmax << "], codomain = [1;" << triangular(dmax) << "]\n";
        return 2;
    }

	// ToDo: Exercise 1.a - print triangular number to console

    pretty_print(triangular(n));

	return 0;
}
