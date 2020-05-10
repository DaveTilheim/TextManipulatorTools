#include "Bool.hpp"


using namespace Lizzy;



Bool::Bool(bool value) : value(value)
{

}

Bool::Bool(string expr)
{
	setFromValue(data);
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
	CONST_CONTROL
	value = newValue;
}

void setFromData(Data *data)
{
	CONST_CONTROL
	Reference::StrictInfer(&data);
	if(dynamic_cast<Bool *>(data))
		set(dynamic_cast<Bool *>(data)->get());
	else if(dynamic_cast<Integer *>(data))
		set(dynamic_cast<Integer *>(data)->get());
	else if(dynamic_cast<Float *>(data))
		set(dynamic_cast<Float *>(data)->get());
	else
		throw Exception("Data is " + data->type() + " (can not convert " + data->type() + " into Bool)");
}

void setFromValue(string value)
{
	CONST_CONTROL
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
