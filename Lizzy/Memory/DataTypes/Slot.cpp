#include "Slot.hpp"

using namespace Lizzy;

#include "Slot.hpp"


Slot::Slot(Data **data) : data(data)
{

}

Slot::Slot(Slot *slot)
{
	attribs = REFERENCE_A;
	referenceTo(slot);
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

void Slot::referenceTo(Slot *slot)
{
	if(isReference())
	{
		if(not slot->isRestrict())
		{
			data = slot->data;
			attribs = REFERENCE_A | slot->attribs;
		}
		else
		{
			Exception("Slot is marked restrict, it can not be referenced");
		}
	}
	else
	{
		throw Exception("Slot is not a Reference");
	}
}

string Slot::toString()
{
	string buf;
	buf += "\tREFERENCE  : "  + (isReference() ? string("YES") : string("NO"));
	buf += "\n\tRESTRICT   : " + (isRestrict() ? string("YES") : string("NO"));
	buf += "\n\tPERSISTANT : " + (isPersistant() ? string("YES") : string("NO"));
	buf += "\n\tFINAL      : " + (isFinal() ? string("YES") : string("NO"));
	buf += "\n\tCONST      : " + (isConst() ? string("YES") : string("NO"));
	buf += "\n";
	buf += "\t" + (*data)->type() + " ** : " + to_string((long long)data) +
	"\n\t" + (*data)->type() + " *  : " + to_string((long long)*data) +
	"\n\t" + (*data)->type() + "    : " + (*data)->toString();
	return buf;
}

string Slot::stack(string id)
{
	string buf = "[" + id + " | " + to_string((long long)data) + " | " + to_string((long long)*data) + " | " + (*data)->toString() + "]";
	return buf;
}