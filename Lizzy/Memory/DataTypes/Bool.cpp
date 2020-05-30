#include "Bool.hpp"


using namespace Lizzy;


Data *(*Data::generateBool)(bool) = [](bool b){return (Data *)new Bool(b);};


Bool::Bool(bool value) : value(value)
{

}

Bool::Bool(string expr)
{
	setFromValue(expr);
}

Bool::Bool(const Bool& cp) : value(cp.value)
{

}

Bool::Bool(Data *data)
{
	setFromData(data);
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

void Bool::setFromData(Data *data)
{
	if(dynamic_cast<Bool *>(data))
		set(dynamic_cast<Bool *>(data)->get());
	else if(dynamic_cast<Integer *>(data))
		set(dynamic_cast<Integer *>(data)->get());
	else if(dynamic_cast<Float *>(data))
		set(dynamic_cast<Float *>(data)->get());
	else
		throw Exception("Data is " + data->type() + " (can not convert " + data->type() + " into Bool)");
}

void Bool::setFromValue(string value)
{
	if(Bool::is(value))
		this->value = value == "true";
	else if(Integer::is(value))
		this->value = atoi(value.c_str());
	else if(Float::is(value))
		this->value = atof(value.c_str());
	else
		throw Exception("Can not set '" + value + "' as Bool value");
}

Bool& Bool::operator=(const Bool& cp)
{
	set(cp.value);
	return *this;
}

bool Bool::is(string expr)
{
	return expr == "true" or expr == "false";
}




