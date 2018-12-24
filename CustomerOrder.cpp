#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Item.h"
#include "CustomerOrder.h"
#include "CustomerItem.h"

size_t CustomerOrder::field_width = 0;



CustomerOrder::CustomerOrder(const std::string &str)
{
	bool is_more = true;
	size_t index = 0;
	Utilities utility;
	this->nOrders = 0;
	this->name = utility.nextToken(str, index, is_more);
	if (this->name.empty())
		throw std::string("*** No Specfied Name To Load ***");
	if (is_more)
	{
		this->product = utility.nextToken(str, index, is_more);
		if (this->product.empty())
			throw std::string("*** No Specfied product To Load ***");
		if (is_more)
		{
			size_t temp_index = index;
			for (; is_more; this->nOrders++)
				utility.nextToken(str, index, is_more);
			if (this->nOrders != 0)
				this->order = new CustomerItem[this->nOrders];
			index = temp_index;
			for (size_t i = 0; i < this->nOrders; ++i)
				this->order[i] = utility.nextToken(str, index, is_more);
		}
	}
	if (utility.getFieldWidth() > this->field_width)
		this->field_width = utility.getFieldWidth();
}
CustomerOrder::CustomerOrder(CustomerOrder&& rhs) NOEXCEPT
{
	*this = std::move(rhs);
}
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& rhs) NOEXCEPT
{
	if (this != &rhs)
	{
		this->order = nullptr;

		this->order = rhs.order;
		this->name = rhs.name;
		this->product = rhs.product;
		this->nOrders = rhs.nOrders;
		this->field_width = rhs.field_width;

		rhs.order = nullptr;
	}
	return std::move(*this);
}

CustomerOrder::CustomerOrder(const CustomerOrder &rhs)
{
	throw std::string("*** can not copy a customer's order ***");

}

CustomerOrder::~CustomerOrder()
{
	delete[] this->order;
}

unsigned int CustomerOrder::noOrders() const
{
	return this->nOrders;
}

const std::string & CustomerOrder::operator[](unsigned int index) const
{
	if (this->nOrders < index)
		throw std::string("*** Index Out Of Reach ***");
	return this->order[index].getName();
}

void CustomerOrder::fill(Item & rhs)
{
	for (size_t i = 0; i < this->nOrders; ++i)
		if (rhs.getName() == this->order[i].getName())
			if (!(this->order[i].isFilled()))
			{
				this->order[i].fill(rhs.getCode());
				rhs++;
			}
}

void CustomerOrder::remove(Item & rhs)
{
	CustomerItem* temp;
	for (size_t i = 0; i < this->nOrders; ++i)
	{
		if (rhs.getName() == this->order[i].getName())
		{
			temp = new CustomerItem[this->nOrders - 1];
			for (size_t x = 0; i < this->nOrders; ++i)
				if (x != i)
					temp[x] = this->order[x];
			this->order = temp;
			this->nOrders = this->nOrders - 1;
			temp = nullptr;

		}
	}
}

bool CustomerOrder::empty() const
{
	return this->nOrders == 0 && this->name.empty();
}

void CustomerOrder::display(std::ostream & os) const
{
	os.fill(' ');
	os << std::setw(this->field_width) << std::left << this->name
		<< ": " << this->product << std::endl;
	for (size_t i = 0; i < this->nOrders; ++i)
	{
		this->order[i].display(os);
		os << std::endl;
	}
}
