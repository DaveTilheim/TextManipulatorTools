#include "Vector.hpp"


using namespace Lizzy;



Vector::Vector()
{

}

Vector::Vector(vector<Data **>& values)
{
	copyVector(values);
}

Vector::Vector(const Vector& cp)
{
	copyVector(cp.value);
}

Vector::Vector(Data *data)
{
	setFromData(data);
}

Vector::~Vector()
{
	for(auto **data : value)
	{
		TRY_SLOT_DELETE(data);
	}
	value.clear();
}

string Vector::toString()
{
	string buf;
	for(auto **data : value)
	{
		buf += (*data)->toString() + " ";
	}
	if(buf.size()) buf.pop_back();
	else return " ";
	return buf;
}

string Vector::type()
{
	return "Vector";
}

Types Vector::typeId()
{
	return VECTOR_T;
}

Data *Vector::dup()
{
	return new Vector(*this);
}

Data **Vector::get(int i) const noexcept(false)
{
	if(i >= value.size()) throw Exception("Index out of band : i=" + to_string(i) + " and Vector size is " + to_string(value.size()));
	return value[i];
}

void Vector::clean()
{
	for(auto **data : value)
	{
		TRY_SLOT_DELETE(data);
	}
	value.clear();
}

void Vector::add(Data **data)
{
	CONST_CONTROL
	value.push_back(data);
}

void Vector::foreach(void (*operation)(Data **))
{
	for(auto **ld : value)
	{
		operation(ld);
	}
}

void Vector::copyVector(const vector<Data **>& vec)
{
	CONST_CONTROL
	value.clear();
	for(auto **data : vec)
	{
		value.push_back(new Data*((*data)->dup()));
	}
}

vector<Data **>& Vector::getVector()
{
	return value;
}

Vector& Vector::operator=(const Vector& cp)
{
	copyVector(cp.value);
	return *this;
}

void Vector::setFromData(Data *data)
{
	if(dynamic_cast<Vector *>(data))
	{
		*this = *dynamic_cast<const Vector *>(data);
	}
	else
	{
		throw Exception("Can not convert " + data->type() + " into Vector");
	}
}

void Vector::setFromValue(string value)
{
	throw Exception("Can not convert " + value + " into Vector");
}
