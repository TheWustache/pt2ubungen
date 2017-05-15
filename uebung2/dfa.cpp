#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string step(std::string state, int value)
{
	// Todo: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}.

	if (state.compare("dispense") == 0)return state;
	switch (value) {
	case 10:
		switch (std::stoi(state)) {
		case 0:return "10";
		case 10:return "20";
		case 20:return "30";
		case 30:return "40";
		case 40:return "dispense";
		}
	case 20:
		switch (std::stoi(state)) {
		case 0:return "20";
		case 10:return "30";
		case 20:return "40";
		case 30:
		case 40:return "dispense";
		}
	case 50:
		return "dispense";
	// for all states and inputs which are not handled above show a message and return original state
	default:
		std::cout << "Invalid input.\n";
		return state;
	}	
	return state;
}


std::string stepExtended(std::string state, int value)
{
	// Todo: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}. Accepted drink selection values are {1, 2, 3}.
	if (state.compare("0") == 0) {
		switch (value) {
		case 1: return "1 : 0";
		case 2: return "2 : 0";
		case 3: return "3 : 0";
		default:
			std::cout << "Invalid input.\n";
			return state;
		}
	}
	//only takes first number
	switch (std::stoi(state)) {
	case 1:
		switch (value) {
		case 10:
			switch (std::stoi(state.substr(3))) {
			case 0:return "1 : 10";
			case 10:return "1 : 20";
			case 20:return "1 : 30";
			case 30:return "1 : 40";
			case 40:return "dispense";
			}
		case 20:
			switch (std::stoi(state.substr(3))) {
			case 0:return "1 : 20";
			case 10:return "1 : 30";
			case 20:return "1 : 40";
			case 30:
			case 40:return "dispense";
			}
		case 50:
			return "dispense";
			// for all states and inputs which are not handled above show a message and return original state
		default:
			std::cout << "Invalid input.\n";
			return state;
		}
	case 2:
		switch (value) {
		case 10:
			switch (std::stoi(state.substr(3))) {
			case 0:return  "2 : 10";
			case 10:return "2 : 20";
			case 20:return "2 : 30";
			case 30:return "2 : 40";
			case 40:return "2 : 50";
			case 50:return "2 : 60";
			case 60:return "2 : 70";
			case 70:return "dispense";

			}
		case 20:
			switch (std::stoi(state.substr(3))) {
			case 0:return  "2 : 20";
			case 10:return "2 : 30";
			case 20:return "2 : 40";
			case 30:return "2 : 50";
			case 40:return "2 : 60";
			case 50:return "2 : 70";
			case 60:
			case 70:return "dispense";
			}
		case 50:
			switch (std::stoi(state.substr(3))) {
			case 0:return  "2 : 50";
			case 10:return "2 : 60";
			case 20:return "2 : 70";
			case 30:
			case 40:
			case 50:
			case 60:
			case 70:return "dispense";
			}

			// for all states and inputs which are not handled above show a message and return original state
		default:
			std::cout << "Invalid input.\n";
			return state;
		}
	case 3:
		switch (value) {
		case 10:
			switch (std::stoi(state.substr(3))) {
			case 0:return "3 : 10";
			case 10:return "3 : 20";
			case 20:return "3 : 30";
			case 30:return "3 : 40";
			case 40:return "3 : 50";
			case 50:return "3 : 60";
			case 60:return "3 : 70";
			case 70:return "3 : 80";
			case 80:return "3 : 90";
			case 90:return "dispense";
			}
		case 20:
			switch (std::stoi(state.substr(3))) {
			case 0:return "3 : 20";
			case 10:return "3 : 30";
			case 20:return "3 : 40";
			case 30:return "3 : 50";
			case 40:return "3 : 60";
			case 50:return "3 : 70";
			case 60:return "3 : 80";
			case 70:return "3 : 90";
			case 80:
			case 90:return "dispense";
			}
		case 50:
			switch (std::stoi(state.substr(3))) {
			case 0:return "3 : 50";
			case 10:return "3 : 60";
			case 20:return "3 : 70";
			case 30:return "3 : 80";
			case 40:return "3 : 90";
			case 50:
			case 60:
			case 70:
			case 80:
			case 90:return "dispense";
			}
			// for all states and inputs which are not handled above show a message and return original state
		default:
			std::cout << "Invalid input.\n";
			return state;
		}
	}

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