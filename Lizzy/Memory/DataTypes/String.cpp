#include "String.hpp"


using namespace Lizzy;



String::String(string value) : value(value)
{

}


String::String(const String& cp) : value(cp.value)
{

}

String::~String()
{

}

string String::toString()
{
	return value.size() ? value : " ";
}

string String::type()
{
	return "String";
}

Types String::typeId()
{
	return STRING_T;
}

Data *String::dup()
{
	return new String(value);
}

string String::get() const
{
	return value;
}

void String::set(string newValue)
{
	value = newValue;
}

String& String::operator=(const String& cp)
{
	value = cp.value;
	return *this;
}

bool String::is(string expr)
{
	return true;
}

char& String::operator[](int i)
{
	return value[i];
}
