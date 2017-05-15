#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>


bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;

	switch (column)
	{
		// example regExp for column 1
		/*case 1:
			regExp = "[a-zA-Z]+";
			break;*/
	case 5:
		regExp = "|{3,4}[a-zA-Z0-9äöüÄÖÜß]";
		break;

		// Todo: implement cases for other columns

		default:
			regExp = ".*";
			break;
	}

	return std::regex_match(teststring, regExp);
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed, line;

	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		std::string field;

		std::vector<std::string> savedLine;
		//with ',' as delim		
		while (std::getline(linestream, field, ',')) {
			savedLine.push_back(field);
		}
		if (savedLine.size() < 12) //Adding "nothing" for missing timezones
			savedLine.push_back("");
		std::cout << savedLine.at(1) << " - " << savedLine.at(11) <<std::endl;

		savedLine.clear();
		// Todo: - Split line and write result to std::cout
		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect function for this


	}
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]" << std::endl;
		return -1; // invalid number of parameters
	}

	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;

	readTokensAndLines(argv[1]);

	return 0;
}
