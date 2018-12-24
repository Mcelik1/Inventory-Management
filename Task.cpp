#include <iostream>
#include <iomanip>
#include <string>
#include "Task.h"
#include "Utilities.h"
size_t Task::field_width = 1;

/*
1. nitializes the number of product slots to a default value of 1
2. the pointers to the next tasks to safe addresses
*/
Task::Task(const std::string& i_data)
{
	Utilities utilities;
	this->slots = "1";
	for (int i = 0; i < 2; i++)
		this->pNextTask[i] = nullptr;
	size_t index = 0;
	bool is_more = true;
	this->name = utilities.nextToken(i_data, index, is_more);
	if (is_more)
	{
		this->slots = utilities.nextToken(i_data, index, is_more);
		for (int i = 0; i < 2; i++)
			if (is_more)
				this->nextTask[i] = utilities.nextToken(i_data, index, is_more);
	}
	this->field_width = utilities.getFieldWidth();
}

/*
This function checks the name of each non-empty next task against task
and, if the names match, stores the address of task in the pointer to
that particular next task.
This function always returns true if both next task names are empty.
*/
bool Task::validate(const Task & i_task)
{
	bool ret_val = false;
	for (auto i = 0; i < 2; i++)
		if (!this->nextTask[i].empty())
			if (this->nextTask[i] == i_task.getName())
				if (this->pNextTask != nullptr)
					this->pNextTask[i] = &i_task;
	if (!this->nextTask[0].empty())
		if (this->pNextTask[0] != nullptr)
			ret_val = true;
	if (!this->nextTask[1].empty())
		if (this->pNextTask[0] == nullptr)
			ret_val = false;
	if (this->nextTask[0].empty() && this->nextTask[1].empty())
		ret_val = true;
	return ret_val;
}

// returns the name of the task
const std::string& Task::getName() const
{
	return this->name;
}
// returns the number of product slots in the task
unsigned int Task::getSlots() const
{
	return std::stoul(this->slots, nullptr, 0);
}
/*
returns the address of the next task associated with the parameter received.

*/
const Task * Task::getNextTask(Quality i_parameter) const
{
	const Task* ret_val = nullptr;
	if (!(this->nextTask[i_parameter].empty()))
		ret_val = this->pNextTask[i_parameter];
	if (ret_val == nullptr)
	{
		std::string exception = "*** Validate [";
		exception += this->nextTask[i_parameter];
		exception += "] @ [";
		exception += this->name;
		exception += "] ***.";
		throw exception;
	}
	return ret_val;
}

void Task::display(std::ostream & os) const
{
	std::string name = "[";
	std::string PassedName = "[";
	std::string ReDirectName = "[";
	name += this->name;
	name += "]";
	if (!this->nextTask[Quality::passed].empty())
		PassedName += this->nextTask[Quality::passed];
	if (!this->nextTask[Quality::redirect].empty())
		ReDirectName += this->nextTask[Quality::redirect];
	ReDirectName += "]";
	PassedName += "]";
	os << std::setw(13) << std::left << "Task Name " << ": " << std::setw(16) << name
		<< "[" << this->slots << "]"
		<< std::endl;
	if (PassedName.size() > 2)
	{
		os << " Continue to : " << std::setw(16) << PassedName;
		if (this->pNextTask[Quality::passed] == nullptr)
			os << "*** to be validated ***";
		os << std::endl;
	}
	if (ReDirectName.size() > 2)
	{
		os << " Redirect to : " << std::setw(16) << ReDirectName;
		if (this->pNextTask[Quality::redirect] == nullptr)
			os << "*** to be validated ***";
		os << std::endl;
	}
}

size_t Task::getFieldWidth()
{
	return field_width;
}

bool operator==(const Task & lhs, const Task & rhs)
{
	return lhs.getName() == rhs.getName();
}
