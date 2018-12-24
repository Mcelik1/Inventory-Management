#include <string>
#include <iostream>
#include <fstream>
#include "Utilities.h"

char Utilities::delimiter = ' ';
std::ofstream Utilities::logFile("default");
Utilities::Utilities() : field_width(1)
{

}
/*
my logic to get rid of the white spaces since i couldnt add it to the class i just made a function and put it here
i hope thats not an issue
*/
std::string eraseWhiteSpace(std::string input)
{
	std::string val;
	int firstNonSpace = input.find_first_not_of(" ");
	int lastNonSpace = input.find_last_not_of(" ");
	if (firstNonSpace != -1)
		val = input.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
	return val;
}
size_t Utilities::getFieldWidth() const
{
	return this->field_width;
}
const std::string Utilities::nextToken(const std::string& i_str, size_t& next_pos, bool& more)
{
	std::string str = eraseWhiteSpace(i_str);
	more = true;
	int delim1_index;
	std::string ret_val;
	std::string exception1 = str + "<-- *** no token found before the delimiter ***";
	std::string exception2 = str + "<-- *** two delims in a row ***";
	delim1_index = str.find(this->delimiter, next_pos);
	if (delim1_index == 0)
		throw exception1;
	ret_val = str.substr(next_pos, delim1_index - next_pos);
	ret_val = eraseWhiteSpace(ret_val);
	next_pos = delim1_index + 1;
	if (delim1_index == -1 || delim1_index == (signed) str.size() - 1)
		more = false;
	if (ret_val.size() > this->field_width)
		this->field_width = ret_val.size();
	if ((unsigned)delim1_index + 1 == str.find(this->delimiter, next_pos) && delim1_index == 0)
		throw exception2;
	return ret_val;
}

void Utilities::setDelimiter(const char delim)
{
	delimiter = delim;
}
void Utilities::setLogFile(const char * i_logFile)
{
	logFile.open(i_logFile);
}

std::ofstream & Utilities::getLogFile()
{
	return logFile;
}

void Utilities::setFieldWidth(size_t fw)
{
	this->field_width = fw;
}

