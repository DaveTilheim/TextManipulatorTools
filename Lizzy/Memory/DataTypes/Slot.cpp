#include "Slot.hpp"

using namespace Lizzy;

#include "Slot.hpp"


Slot::Slot(Data **data) : data(data)
{

}

Slot::~Slot()
{
	tryDelete();
}

bool Slot::isReference()
{
	return attribs & REFERENCE_A;
}

bool Slot::isPersistant()
{
	return attribs & PERSISTANT_A;
}

bool Slot::isDeleteable()
{
	return not isReference() and not isPersistant();
}

bool Slot::isRestrict()
{
	return attribs & RESTRICT_A;
}

bool Slot::isFinal()
{
	return attribs & FINAL_A;
}

bool Slot::isConst()
{
	return attribs & CONST_A;
}

void Slot::tryDelete()
{
	if(isDeleteable())
	{
		delete *data;
		*data = nullptr;
		delete data;
		data = nullptr;
	}
}
