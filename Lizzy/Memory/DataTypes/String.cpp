#include "String.hpp"


using namespace Lizzy;

Data *(*Data::generateString)(string) = [](string s){return (Data *)new String(s);};

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
	value = newValue;
}

void String::setFromValue(string value)
{
	this->value = value;
}

void String::setFromData(Data *data)
{
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

string String::getCharAt(string iexpr)
{
	if(Integer::is(iexpr))
	{
		int i = atoi(iexpr.c_str());
		if(i >= 0 and i < value.size())
		{
			return string(1, value[i]);
		}
		throw Exception("Index out of band. " + to_string(i) + " give but boundaries are: [0, " + to_string(value.size() - 1) + "]");
	}
	throw Exception(iexpr + " can not be interpreted as String index");
}

void String::setCharAt(string iexpr, string chars)
{
	if(Integer::is(iexpr))
	{
		int i = atoi(iexpr.c_str());
		if(i >= 0 and i < value.size())
		{
			if(chars.size() == 1)
			{
				value[i] = chars[0];
			}
			else
			{
				throw Exception(to_string(chars.size()) + " characers given but expected 1");
			}
		}
		else
			throw Exception("Index out of band. " + to_string(i) + " give but boundaries are: [0, " + to_string(value.size() - 1) + "]");
	}
	else
		throw Exception(iexpr + " can not be interpreted as String index");
}


