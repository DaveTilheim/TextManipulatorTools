#include "Slot.hpp"

using namespace Lizzy;


string Slot::toString()
{
	if(*dataPointer)
		return (*dataPointer)->toString();
	throw Exception("Slot is empty");
}


string Slot::type()
{
	if(*dataPointer)
		return (*dataPointer)->type();
	throw Exception("Slot is empty");
}

Types Slot::typeId()
{
	if(*dataPointer)
		return (*dataPointer)->typeId();
	throw Exception("Slot is empty");
}

Data *Slot::dup()
{
	if(*dataPointer)
		return (*dataPointer)->dup();
	throw Exception("Slot is empty");
}

void Slot::setFromData(Data* data)
{
	if(*dataPointer)
		(*dataPointer)->setFromData(data);
	else
		throw Exception("Slot is empty");
}

void Slot::setFromValue(string value)
{
	if(*dataPointer)
		(*dataPointer)->setFromValue(value);
	else
		throw Exception("Slot is empty");
}

Data *Slot::get()
{
	if(*dataPointer)
		return *dataPointer;
	throw Exception("Slot is empty");
}

Slot::operator Data*()
{
	return get();
}

Slot::operator Bool*()
{
	return dynamic_cast<Bool *>(get());
}

Slot::operator Float*()
{
	return dynamic_cast<Float *>(get());
}

Slot::operator Integer*()
{
	return dynamic_cast<Integer *>(get());
}

Slot::operator Reference*()
{
	return dynamic_cast<Reference *>(get());
}

Slot::operator String*()
{
	return dynamic_cast<String *>(get());
}

Slot::operator Table*()
{
	return dynamic_cast<Table *>(get());
}

Slot::operator Vector*()
{
	return dynamic_cast<Vector *>(get());
}
