#include "Vector.hpp"


using namespace Lizzy;



Vector::Vector()
{

}

Vector::Vector(const Vector& cp)
{
	copyVector(cp.value);
}

Vector::~Vector()
{
	for(auto *data : value)
	{
		delete data;
	}
}

string Vector::toString()
{
	string buf;
	for(auto *data : value)
	{
		buf += data->toString() + " ";
	}
	if(buf.size()) buf.pop_back();
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

Data *Vector::get(int i) const noexcept(false)
{
	if(i >= value.size()) throw Exception("Index out of band : i=" + to_string(i) + " and Vector size is " + to_string(value.size()));
	return value[i];
}

void Vector::set(Data& newData, int i) noexcept(false)
{
	if(i >= value.size()) throw Exception("Index out of band : i=" + to_string(i) + " and Vector size is " + to_string(value.size()));
	value[i] = newData.dup();
}

void Vector::remove(int i) noexcept(false)
{
	if(i >= value.size()) throw Exception("Index out of band : i=" + to_string(i) + " and Vector size is " + to_string(value.size()));
	delete value[i];
	value.erase(value.begin() + i);
}

void Vector::clean()
{
	for(auto *data : value)
	{
		delete data;
	}
	value.clear();
}

void Vector::add(Data &data)
{
	value.push_back(data.dup());
}

void Vector::foreach(void (*operation)(Data *))
{
	for(auto *ld : value)
	{
		operation(ld);
	}
}

void Vector::copyVector(const vector<Data *>& vec)
{
	for(auto *data : vec)
	{
		value.push_back(data->dup());
	}
}

vector<Data *>& Vector::getVector()
{
	return value;
}

Vector& Vector::operator=(const Vector& cp)
{
	copyVector(cp.value);
	return *this;
}
