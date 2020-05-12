#include "Float.hpp"


using namespace Lizzy;

Data *(*Data::generateFloat)(double) = [](double d){return (Data *)new Float(d);};


Float::Float(double value) : value(value)
{

}

Float::Float(string expr)
{
	setFromValue(expr);
}

Float::Float(Data *data)
{
	setFromData(data);
}

Float::Float(const Float& cp) : value(cp.value)
{

}

Float::~Float()
{

}

string Float::toString()
{
	return to_string(value);
}

string Float::type()
{
	return "Float";
}

Types Float::typeId()
{
	return FLOAT_T;
}

Data *Float::dup()
{
	return new Float(value);
}

double Float::get() const
{
	return value;
}

void Float::set(double newValue)
{
	value = newValue;
}

Float& Float::operator=(const Float& cp)
{
	set(cp.value);
	return *this;
}

void Float::setFromData(Data *data)
{
	if(dynamic_cast<Float *>(data))
		set(dynamic_cast<Float *>(data)->get());
	else if(dynamic_cast<Integer *>(data))
		set(dynamic_cast<Integer *>(data)->get());
	else if(dynamic_cast<Bool *>(data))
		set(dynamic_cast<Bool *>(data)->get());
	else
		throw Exception("Data is " + data->type() + " (can not convert " + data->type() + " into Float)");
}

void Float::setFromValue(string value)
{
	if(Integer::is(value) or Float::is(value))
		set(atof(value.c_str()));
	else if(Bool::is(value))
		set(value == "true");
	else
		throw Exception("Can not set '" + value + "' as Float value");
}

bool Float::is(string expr)
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
