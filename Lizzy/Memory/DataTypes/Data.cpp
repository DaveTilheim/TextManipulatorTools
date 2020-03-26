#include "Data.hpp"

using namespace Lizzy;



string Lizzy::getAttrAsString(int attr)
{
	switch(attr)
	{
		case CONST_A: return "const";
		case FINAL_A: return "final";
		default: return "unknown attribute";
	}
}


Data::~Data()
{

}

int Data::getAttr()
{
	return attr;
}

void Data::setAttr(int dattr)
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


