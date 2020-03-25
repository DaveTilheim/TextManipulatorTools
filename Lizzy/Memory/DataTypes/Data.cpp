#include "Data.hpp"

using namespace Lizzy;

Data::~Data()
{

}

DataAttributes& Data::getAttr()
{
	return attr;
}

void Data::setAttr(const DataAttributes& dattr)
{
	attr = dattr;
}

string Data::type()
{
	return "undefined";
}

Types Data::typeId()
{
	return NONE_T;
}


Data* Data::dup()
{
	return nullptr;
}


