#include "Bool.hpp"


using namespace Lizzy;



Bool::Bool(bool value) : value(value)
{

}

Bool::Bool(string expr) : value(expr == "true")
{

}

Bool::Bool(const Bool& cp) : value(cp.value)
{

}

Bool::~Bool()
{

}

string Bool::toString()
{
	return value ? "true" : "false";
}

string Bool::type()
{
	return "Bool";
}

Types Bool::typeId()
{
	return BOOL_T;
}

Data *Bool::dup()
{
	return new Bool(value);
}

bool Bool::get() const
{
	return value;
}

void Bool::set(bool newValue)
{
	value = newValue;
}

Bool& Bool::operator=(const Bool& cp)
{
	value = cp.value;
	return *this;
}

bool Bool::is(string expr)
{
	return expr == "true" or expr == "false";
}
