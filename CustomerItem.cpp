#include <iomanip>
#include "Item.h"
#include "CustomerItem.h"





CustomerItem::CustomerItem(const std::string & str)
{
	if (!str.empty())
		this->name = str;
	this->filled = false;
}

bool CustomerItem::asksFor(const Item& i_item) const
{

	return this->name == i_item.getName();;
}

bool CustomerItem::isFilled() const
{
	return this->filled;
}

void CustomerItem::fill(const unsigned int i_code)
{
	this->code = i_code;
	this->filled = true;
}

void CustomerItem::clear()
{
	this->code = 0;
	this->filled = false;
}

const std::string & CustomerItem::getName() const
{
	return this->name;
}

void CustomerItem::display(std::ostream & os) const
{
	unsigned temp_code = 0;
	if (filled)
		temp_code = this->code;
	os.fill('0');
	os << " + [" << std::setw(CODE_WIDTH) << std::right << temp_code << "] " << this->name;
}
