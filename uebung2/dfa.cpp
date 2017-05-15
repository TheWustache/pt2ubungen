#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string step(std::string state, int value)
{
	// Todo: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}.




	// for all states and inputs which are not handled above show a message and return original state
	std::cout << "Invalid input.\n";
	return state;
}


std::string stepExtended(std::string state, int value)
{
	// Todo: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}. Accepted drink selection values are {1, 2, 3}.




	// for all states and inputs which are not handled above show a message and return original state
	std::cout << "Invalid input.\n";
	return state;
}


int main(int argc, char * argv[])
{
	std::string state = "0";
	bool extendedMode = false;

	if(argc == 2)
		extendedMode = true;

	while(true)
	{
		int value = 0;
		std::string input;
		if(state == "0" && extendedMode)
			std::cout << "Current state: " << state << ". Please select a drink (1, 2, 3): ";
		else
			std::cout << "Current state: " << state << ". Please input a coin (10, 20, 50): ";
		std::getline(std::cin, input);
		std::stringstream(input) >> value;

		state = extendedMode ? stepExtended(state, value) : step(state, value);

		if(state == "dispense")
		{
			std::cout << "Here is your drink. Goodbye!\n\n";
			state = "0";
		}
	}
}
