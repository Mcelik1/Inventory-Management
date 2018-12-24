#include <iostream>
#include <algorithm>
#include "Item.h"
#include "ItemManager.h"
#include "OrderManager.h"
#include "CustomerOrder.h"
CustomerOrder && OrderManager::extract()
{
	return std::move(*this->end());

}

void OrderManager::validate(const ItemManager & Man_item, std::ostream & os)
{

	for (size_t Cust_index = 0; Cust_index < this->size(); ++Cust_index)
	{
		for (size_t Order_index = 0; Order_index < this->at(Cust_index).noOrders(); Order_index++)
		{
				if (std::find_if(Man_item.begin(), Man_item.end(), [&](Item item) {return this->at(Cust_index)[Order_index] == item.getName(); }) == Man_item.end())
				{
					os << this->at(Cust_index)[Order_index] << " is not available" << std::endl;
					break;
				}	
		}
	}
}

void OrderManager::display(std::ostream & os) const
{
	for (size_t i = 0; i < this->size(); ++i)
		this->at(i).display(os);
}
