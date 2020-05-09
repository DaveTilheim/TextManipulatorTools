#include "Reference.hpp"


using namespace Lizzy;





Reference::Reference()
{
	dataPointer = new Data*;
	*dataPointer = nullptr;
}

Reference::Reference(Reference& other)
{
	dataPointer = new Data*;
	*dataPointer = other.dup();
}

Reference::Reference(Data *data)
{
	dataPointer = new Data*;
	*dataPointer = data->dup();
}

Reference::Reference(Data **data)
{
	dataPointer = data;
}

Reference::~Reference()
{
	if(*dataPointer)
	{
		delete *dataPointer;
		*dataPointer = nullptr;
	}
	delete dataPointer;
}

int Reference::getAttr()
{
	if(*dataPointer)
		return (*dataPointer)->getAttr();
	throw Exception("Reference is empty");
}

void Reference::setAttr(int attr)
{
	if(*dataPointer)
		(*dataPointer)->setAttr(attr);
	else
		throw Exception("Reference is empty");
}

string Reference::toString()
{
	if(*dataPointer)
		return (*dataPointer)->toString();
	return "null";
}


string Reference::type()
{
	if(*dataPointer)
		return (*dataPointer)->type();
	return "Reference";
}

Types Reference::typeId()
{
	if(*dataPointer)
		return (*dataPointer)->typeId();
	return REFERENCE_T;
}

Data *Reference::dup()
{
	if(*dataPointer)
		return (*dataPointer)->dup();
	return new Reference();
}

void Reference::set(Data* data)
{
	if(*dataPointer)
		(*dataPointer)->set(data);
	else
		*dataPointer = data;
}

void Reference::set(Data** data)
{
	if(*dataPointer)
		delete *dataPointer;
	delete *dataPointer;
	dataPointer = data;
}

Data *Reference::get()
{
	if(*dataPointer)
		return *dataPointer;
	return nullptr;
}

Data **Reference::getSlot()
{
	return dataPointer;
}

bool Reference::isEmpty() const
{
	return *dataPointer == nullptr;
}

int Reference::getSlotAttr() const
{
	return attr;
}

void Reference::setSlotAttr(int attr)
{
	Data::setAttr(attr);
}

Reference& Reference::operator=(Reference& other)
{
	set(other.get());
	return *this;
}

static void Reference::StrictInfer(Data **ref)
{
	if(dynamic_cast<Reference *>(*ref))
	{
		if(dynamic_cast<Reference *>(*ref)->get())
		{
			*ref = dynamic_cast<Reference *>(*ref)->get();
		}
		else
		{
			throw Exception("Reference to null");
		}
	}
}


