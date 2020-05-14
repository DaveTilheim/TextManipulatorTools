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
	cout << "Slot removed" << endl;
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

Data **Slot::get()
{
	if(data)
		return data;
	else
		throw Exception("Access to null value");
}

void Slot::referenceTo(Slot *slot)
{
	if(slot == nullptr)
	{
		data = nullptr;
		attribs = REFERENCE_A;
		return;
	}
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
	string type = data == nullptr ? "null" : (*data)->type();
	string ptrPtrValue = data == nullptr ? "null" : to_string((long long)data);
	string ptrValue = data == nullptr ? "null" : to_string((long long)*data);
	string value = data == nullptr ? "null" : (*data)->toString();
	string buf;
	buf += "\tREFERENCE  : "  + (isReference() ? string("YES") : string("NO"));
	buf += "\n\tRESTRICT   : " + (isRestrict() ? string("YES") : string("NO"));
	buf += "\n\tPERSISTANT : " + (isPersistant() ? string("YES") : string("NO"));
	buf += "\n\tFINAL      : " + (isFinal() ? string("YES") : string("NO"));
	buf += "\n\tCONST      : " + (isConst() ? string("YES") : string("NO"));
	buf += "\n";
	buf += "\t" + type + " ** : " + ptrPtrValue +
	"\n\t" + type + " *  : " + ptrValue +
	"\n\t" + type + "    : " + value;
	return buf;
}
