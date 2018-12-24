#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Item.h"
size_t Item::field_width = 0;
/*
code to the default initial code (1).
description string to "no detailed description"
first token as the name
second token as the name of the filler
the third token as the naem of the remover
The fourth token is the integer holding the code to be
*/
Item::Item(const std::string & str)
{
	bool is_more = true;
	size_t index = 0;
	Utilities utility;
	this->code = 1;
	this->description = "no detailed description";
	this->name = utility.nextToken(str, index, is_more);
	if (this->name.empty())
		throw std::string("*** No Specfied Name To Load ***");
	if (utility.getFieldWidth() > this->field_width)
		this->field_width = utility.getFieldWidth();
	if (is_more)
	{
		this->filler = utility.nextToken(str, index, is_more);
		if (this->filler.empty())
			throw std::string("*** No Specfied Filler To Load ***");
		if (is_more)
		{
			this->remover = utility.nextToken(str, index, is_more);
			if (this->remover.empty())
				throw std::string("*** No Specfied Remover To Load ***");
		}
		if (is_more)
		{
			std::string temp_str_code = utility.nextToken(str, index, is_more);
			this->code = std::stoul(temp_str_code, nullptr, 0);
		}
		if (is_more)
			this->description = utility.nextToken(str, index, is_more);
	}


}

bool Item::empty() const
{
	return this->name.empty() && this->code == 1;
}

int Item::operator++(int)
{
	return this->code++;
}

unsigned int Item::getCode() const
{
	return this->code;
}

const std::string & Item::getName() const
{
	return this->name;
}

const std::string & Item::getFiller() const
{
	return this->filler;
}

const std::string & Item::getRemover() const
{
	return this->remover;
}

void Item::display(std::ostream & os, bool flag) const
{
	os.fill(' ');
	os << std::setw(this->field_width) << std::left << this->name;
	os.fill('0');
	os << "[" << std::setw(CODE_WIDTH) << std::right << this->code << "] ";
	if (flag)
	{
		os.fill(' ');
		os << "from " << std::setw(this->field_width) << std::left << this->filler
			<< "to " << std::setw(this->field_width) << std::left << this->remover
			<< std::endl << std::setw(this->field_width + CODE_WIDTH + 5) << std::right << ": " << this->description;
	}
	os << std::endl;
}
