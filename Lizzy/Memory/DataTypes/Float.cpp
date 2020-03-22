#include "Float.hpp"


using namespace Lizzy;



Float::Float(double value) : value(value)
{

}

Float::Float(string expr) : value(atof(expr.c_str()))
{

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
	value = cp.value;
	return *this;
}

bool Float::is(string expr)
{
	auto len = expr.size();
	int ptCounter = 0;
	for(int i = 0; i < len; i++)
	{
		if(not i and expr[i] == '-') continue;
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
