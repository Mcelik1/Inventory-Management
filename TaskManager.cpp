#include <iostream>
#include <algorithm>
#include "Item.h"
#include "ItemManager.h"
#include "Task.h"
#include "TaskManager.h"


void TaskManager::validate(std::ostream & os)
{
	bool is_validate = false;
	for (size_t i = 0; i < this->size(); ++i)
	{
		for (size_t x = 0; x <= this->size() - 1; ++x)
			if (this->at(i).validate(this->at(x)))
				is_validate = true;
		if (!(is_validate))
		{
			os << "not all Tasks are validated" << std::endl;
			break;
		}
	}

}

void TaskManager::validate(const ItemManager & Man_item, std::ostream & os)
{

	for (size_t item_index = 0; item_index < Man_item.size(); ++item_index)
	{
		bool Filler_validate = false;
		bool Remover_validate = false;
		std::vector<Item>::iterator Iterator_temp;
		if (std::find_if(this->begin(), this->end(), [&](Task task) {return Man_item.at(item_index).getFiller() == task.getName(); }) != this->end())
			Filler_validate = true;
		if (std::find_if(this->begin(), this->end(), [&](Task task) {return Man_item.at(item_index).getRemover() == task.getName(); }) != this->end())
			Remover_validate = true;
		if (!(Filler_validate))
			os << Man_item.at(item_index).getFiller() << " is not available" << std::endl;
		if (!(Remover_validate))
			os << Man_item.at(item_index).getRemover() << " is not available" << std::endl;
	}
}


void TaskManager::display(std::ostream & os) const
{
	for (size_t i = 0; i < this->size(); ++i)
		this->at(i).display(os);
}
