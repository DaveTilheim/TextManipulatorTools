#include "Integer.hpp"


using namespace Lizzy;

Data *(*Data::generateInteger)(int) = [](int i){return (Data *)new Integer(i);};

Integer::Integer(long value) : value(value)
{
	
}

Integer::Integer(string expr)// : value(atoi(expr.c_str()))
{
	setFromValue(expr);
}

Integer::Integer(const Integer& cp) : value(cp.value)
{

}

Integer::Integer(Data *data)
{
	setFromData(data);
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

void Integer::setFromData(Data *data)
{
	if(dynamic_cast<Integer *>(data))
	{
		set(dynamic_cast<Integer *>(data)->get());
	}
	else if(dynamic_cast<Float *>(data))
	{
		set(dynamic_cast<Float *>(data)->get());
	}
	else if(dynamic_cast<Bool *>(data))
	{
		set(dynamic_cast<Bool *>(data)->get());
	}
	else
	{
		throw Exception("Data is " + data->type() + " (can not convert " + data->type() + " into Integer)");
	}
}

void Integer::setFromValue(string value)
{
	if(Integer::is(value) or Float::is(value))
		set(atoi(value.c_str()));
	else if(Bool::is(value))
		set(value == "true");
	else
		throw Exception("Can not set '" + value + "' as Integer value");
}

Integer& Integer::operator=(const Integer& cp)
{
	set(cp.get());
	return *this;
}

bool Integer::is(string expr)
{
	auto len = expr.size();
	for(int i = (expr[0] == '-'); i < len; i++)
	{
		if(not isdigit(expr[i])) return false;
	}
	return true;
}



