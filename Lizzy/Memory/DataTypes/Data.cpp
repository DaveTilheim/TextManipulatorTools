#include "Data.hpp"

using namespace Lizzy;



string Lizzy::getAttrAsString(int attr)
{
	switch(attr)
	{
		case CONST_A: return "const";
		case FINAL_A: return "final";
		case RESTRICT_A: return "restrict";
		case PERSISTANT_A: return "persistant";
		default: return "unknown attribute";
	}
}


Data::~Data()
{
	cout << "Data deleted " << this << endl;
}

int Data::getAttr()
{
	return attr;
}

void Data::setAttr(int dattr)
{
	if(attr & dattr) throw Exception("Attribut already set: " + getAttrAsString(dattr));
	if(dattr == RESTRICT_A)
	{
		if(attr & PERSISTANT_A) throw Exception(getAttrAsString(dattr) + " attribute can not be set because Data is persistant");
	}
	else if(dattr == PERSISTANT_A)
	{
		if(attr & RESTRICT_A) throw Exception(getAttrAsString(dattr) + " attribute can not be set because Data is restrict");
	}
	attr = attr | dattr;
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

void Data::setFromData(Data* data)
{

}

void Data::setFromValue(string value)
{

}

bool Data::hasAttr(DataAttributes attr)
{
	return getAttr() & (int)attr;
}


bool Data::isInteger(string expr)
{
	auto len = expr.size();
	for(int i = (expr[0] == '-'); i < len; i++)
	{
		if(not isdigit(expr[i])) return false;
	}
	return true;
}

bool Data::isFloat(string expr)
{
	auto len = expr.size();
	int ptCounter = 0;
	for(int i = expr[i] == '-'; i < len; i++)
	{
		if(not isdigit(expr[i]))
		{
			if(i != 0 and i != len -1 and ptCounter == 0 and expr[i] == '.')
			{
				ptCounter++;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool Data::isBool(string expr)
{
	return expr == "true" or expr == "false";
}
