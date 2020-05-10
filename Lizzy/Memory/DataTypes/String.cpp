#include "String.hpp"


using namespace Lizzy;



String::String(string value)
{
	setFromValue(value);
}


String::String(const String& cp) : value(cp.value)
{

}

String::String(Data *data)
{
	setFromData(data);
}

String::~String()
{
	cout << "ERASE STRING" << endl;
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
	CONST_CONTROL
	value = newValue;
}

void String::setFromValue(string value)
{
	CONST_CONTROL
	this->value = value;
}

void String::setFromData(Data *data)
{
	CONST_CONTROL
	Reference::StrictInfer(&data);
	value = data->toString();
}

String& String::operator=(const String& cp)
{
	set(cp.value);
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
