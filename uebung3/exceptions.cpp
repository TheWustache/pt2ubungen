#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <ctime>

// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date)
{
	std::tm t;
#if defined(__GNUC__) && (__GNUC__ < 5)
	strptime(date.c_str(), "%d.%m.%Y", &t);
#else
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%d.%m.%Y");
#endif

	if(t.tm_year < 105 || t.tm_year > 115)
		throw std::logic_error("Year should be between 2005 and 2015");

	return t;
}

struct FormatException
{
	int m_actLine;
	std::string m_actFields;
};

void parseLine(std::string line, int lineNum)
{
	const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof.
	// Catch all exceptions thrown by these methods.
	// If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.

    try {
        // parse line
        std::stringstream ss(line);
        ss.exceptions(std::ios::failbit | std::ios::badbit);
        std::string fields[3];
        
        for(int i=0; i<3; i++) {
            getline(ss, fields[i], ';');
        }
        
        // check fields
        bool error = false;
        FormatException e = {lineNum, ""};
        
        // Date
        try {
            stringToTime(fields[0]);
        }
        catch (std::logic_error &x) {
            e.m_actFields += fieldNames[0];
            error = true;
        }
        
        // Temperature
        try {
            std::stof(fields[1]);
        }
        catch (std::logic_error &x) {
            e.m_actFields += (e.m_actFields == "" ? "" : ", ") + fieldNames[1];
            error = true;
        }
        
        // Rainfall
        try {
            std::stof(fields[2]);
        }
        catch (std::logic_error &x) {
            e.m_actFields += (e.m_actFields == "" ? "" : ", ") + fieldNames[2];
            error = true;
        }
        
        if(error) {
            throw e;
        }
    }
    catch (std::ios::failure &fail) {
        std::cout << "Error parsing stringstream: " << fail.what();
    }
    catch (FormatException &e) {
        throw e;
    }
}

// TODO 3.1d
void writeOutFormatException(const FormatException& e)
{
    std::ofstream log;
    static bool initialized = false;
    
    try {
        if(!initialized) {
            log.open("../log.txt", std::ios::trunc);
            initialized = true;
        }
        else {
            log.open("../log.txt", std::ios::app);
        }
        
        log.exceptions(std::ios::failbit);
        
        log << e.m_actLine << ": " << e.m_actFields << std::endl;
        
        log.close();
    }
    catch (std::ios::failure &fail) {
        std::cout << "Error opening/reading/closing log: " << fail.what() << std::endl;
    }
    
}

void checkData(std::string path)
{
	int validLines = 0;
	int invalidLines = 0;
	std::ifstream file;

	// TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
    try {
        // open file
        file.open(path);
        file.exceptions(std::ios::failbit);
    
    
        // TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines

        // call parseLine for each line
        std::string line;
        int count = 0;
        
        // skip first line
        std::getline(file, line);
        
        while(std::getline(file, line)) {
            count++;
            try {
                parseLine(line, count);
                validLines++;
            }
            catch (FormatException &e) {
                invalidLines++;
                writeOutFormatException(e);
            }
        }

        // close file
        file.close();
        
        std::cout << "valid data fields: " << validLines << " - invalid data fields: " << invalidLines << std::endl;
    }
    catch (std::ios::failure &fail) {
        std::cout << "Error opening/reading/closing file: " << fail.what() << std::endl;
    }
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}

	checkData(argv[1]);

	return 0;
}
