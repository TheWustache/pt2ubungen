#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>


bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;

	switch (column)//column starting at 0
	{
		// example regExp for column 1
		/*case 1:
			regExp = "[a-zA-Z]+";
			break;*/
	case 5:	//empty string or 3-4 Letter code
		regExp = "(^$)|([a-zA-Z0-9äöüÄÖÜß]{3,4})";
		break;
	case 8: // 0 - 29999, mit führenden 0
		regExp = "[0]*[1-2]?[0-9]{1,4}";
		break;
	case 10: //
		regExp = "[EASOZNU]";
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

		std::vector<std::string> savedLine;			
		char c = '0';
		bool isError = false;
		int errorCode = -1;
		//end at end of line

		for (int i = 0; i < line.size();) {			
			bool stringFlag = false;
			c = '\0';
			parsed = "";
			//1 word, end if linesize is reached or new ,
			while((stringFlag || c != ',' )&& i!=line.size()){// old code  :while (std::getline(linestream, parsed, ',')) {
				c = line[i];
				i++;
				if (c == '\"') {
					stringFlag = !stringFlag;
					continue;
				}
				if (!stringFlag && c == ',')
					break;
				//add char to string
				parsed+=c;				
			}
			//save string
			savedLine.push_back(parsed);
			//errorhandling, once per line if error is found
			if (!isError) {				
				errorCode = (int) savedLine.size() - 1;
				//check if error happened
				isError = !isValueCorrect(savedLine.at(errorCode), errorCode);
				if(isError){
					if (!errorLog.is_open()) {
						errorLog.open("fileio.log");
					}
					errorLog << line << "  -  Error at Field:" << errorCode << std::endl;
				}
			}
		}
		//Adding "nothing" for missing timezones since its the end of the line, otherwise out of bounds exception
		if (savedLine.size() < 12) 
			savedLine.push_back("");
		std::cout << savedLine.at(1) << " - " << savedLine.at(11) <<std::endl;

		//write Error, Works but other stuff didnt
		savedLine.clear();
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
