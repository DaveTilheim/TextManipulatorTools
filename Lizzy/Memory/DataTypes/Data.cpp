#include "Data.hpp"

using namespace Lizzy;



Data::~Data()
{
	cout << "Data deleted " << this << endl;
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

