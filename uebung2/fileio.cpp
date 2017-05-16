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
	case 5:	//empty string or 3-4 Letter code
		regExp = "([]*)|([a-zA-Z0-9‰ˆ¸ƒ÷‹ﬂ]{3,4})";
		break;
	case 8: // 0 - 29999
		regExp = "[0-2]?[0-9]{1,4}";
		break;
	case 10: //
		regExp = "[EASOZNU]{1}";
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

	std::ofstream errorLog;

	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);		
		std::vector<std::string> savedLine;
		
		while (std::getline(linestream, parsed, ',')) {
			
			
			savedLine.push_back(parsed);
			
		}
		//Adding "nothing" for missing timezones since its the end of the line
		if (savedLine.size() < 12) 
			savedLine.push_back("");
		std::cout << savedLine.at(1) << " - " << savedLine.at(11) <<std::endl;

		//write Error, Works but other stuff didnt

		/*if (isError) {
			if (!errorLog.is_open()) {
				errorLog.open("fileio.log");
			}
			errorLog << line << "  -  Error at Field:" << errorCode << std::endl;
		}*/

		savedLine.clear();
		// Todo: - Split line and write result to std::cout
		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect function for this


	}
		if (errorLog.is_open())errorLog.close();
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
