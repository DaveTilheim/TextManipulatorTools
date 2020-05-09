#include "Integer.hpp"


using namespace Lizzy;



Integer::Integer(long value) : value(value)
{
	
}

Integer::Integer(string expr) : value(atoi(expr.c_str()))
{

}

Integer::Integer(const Integer& cp) : value(cp.value)
{

}

Integer::~Integer()
{
	
}

string Integer::toString()
{
	return to_string(value);
}

string Integer::type()
{
	return "Integer";
}

Types Integer::typeId()
{
	return INTEGER_T;
}

Data *Integer::dup()
{
	return new Integer(value);
}

long Integer::get() const
{
	return value;
}

void Integer::set(long newValue)
{
	value = newValue;
}

Integer& Integer::operator=(const Integer& cp)
{
	value = cp.value;
	return *this;
}

bool Integer::is(string expr)
{
	auto len = expr.size();
	for(int i = 0; i < len; i++)
	{
		if(not i and expr[i] == '-') continue;
		if(not isdigit(expr[i])) return false;
	}
	return true;
}