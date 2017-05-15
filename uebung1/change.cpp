
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>

void change(const int due, const int paid, std::ostream& out)
{
    int remaining = paid - due;
    
    // array with cent amounts
    const int MONEY_TYPES = 12;
    int money[MONEY_TYPES] = {5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    
    // ToDo: compute and print set of change tuples
    out << "coin, num" << std::endl;
    
    for(int i=0; i < MONEY_TYPES; i++) {
        if(remaining >= money[i]) {
            out << money[i] << ", " << remaining / money[i] << std::endl;
            remaining -= (remaining / money[i]) * money[i];
        }
    }
}

int main(int argc, char * argv[])
{
    try{
	if(argc != 3 && argc != 5)
		return 1;	// invalid number of parameters

	int due = std::stoi(argv[1]);
	int paid = std::stoi(argv[2]);

	// ToDo: catch invalid arguments
    if(due > paid || due < 0 || paid < 0) {
        return 1;
    }
    
    if(argc == 5 && strcmp(argv[3], "-o") == 0) {
        // create output stream and pass to change
        std::ofstream ofs(argv[4], std::ios::trunc);
        if(ofs.good()) {
            change(due, paid, ofs);
        }
        else {
            return 1;
        }
    }
    else if (argc == 3) {
        change(due, paid, std::cout);
    }
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    };

	// ToDo: print change data as CSV to console

	return 0;
}
