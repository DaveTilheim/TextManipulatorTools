#include "Slot.hpp"

using namespace Lizzy;


Slot::Slot()
{
	dataPointer = new Data*;
	*dataPointer = nullptr;
}

Slot::Slot(Slot& other)
{
	dataPointer = new Data*;
	*dataPointer = other.dup();
}

Slot::Slot(string strvalue)
{

}

Slot::Slot(Data *data)
{
	dataPointer = new Data*;
	*dataPointer = data->dup();
}

Slot::~Slot()
{
	if(*dataPointer)
	{
		delete *dataPointer;
	}
	delete dataPointer;
}

int Slot::getAttr()
{
	if(*dataPointer)
		return (*dataPointer)->getAttr();
	throw Exception("Slot is empty");
}

void Slot::setAttr(int attr)
{
	if(*dataPointer)
		(*dataPointer)->setAttr(attr);
	else
		throw Exception("Slot is empty");
}

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

void Slot::set(Data* data)
{
	if(*dataPointer)
		(*dataPointer)->set(data);
	else
		throw Exception("Slot is empty");
}

Data *Slot::get()
{
	if(*dataPointer)
		return *dataPointer;
	throw Exception("Slot is empty");
}

Data **Slot::getSlot()
{
	return dataPointer;
}

bool Slot::isEmpty() const
{
	return *dataPointer == nullptr;
}

int Slot::getSlotAttr() const
{
	return attr;
}

void Slot::setSlotAttr(int attr)
{
	Data::setAttr(attr);
}

Slot& Slot::operator=(Slot& other)
{
	set(other.get());
	return *this;
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


