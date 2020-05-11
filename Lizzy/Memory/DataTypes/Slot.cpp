#include "Slot.hpp"

using namespace Lizzy;


Slot::~Slot()
{
	if(*dataPointer)
	{
		TRY_DELETE(*dataPointer);
	}
	cout << "Slot deleted " << this << endl;
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

void Slot::setData(Data *data)
{

	Data *tmp = *dataPointer;
	Reference::StrictInfer(&tmp);
	if(tmp)
	{
		if(((tmp)->getAttr() & FINAL_A) == 0)
		{
			CONST_CONTROL_(tmp)
			TRY_DELETE(tmp);
			tmp = data->dup();
			if(dynamic_cast<Reference *>(*dataPointer))
			{
				*dynamic_cast<Reference *>(*dataPointer)->getSlot() = tmp;
			}
			else
			{
				*dataPointer = tmp;
			}
		}
		else
		{
			(tmp)->setFromData(data);
		}
	}
	else
	{
		throw Exception("Slot is empty");
	}
}

void Slot::setData(string value)
{
	Data *tmp = *dataPointer;
	cout << "SET " << value << endl;
	Reference::StrictInfer(&tmp);
	if(tmp)
	{
		if(((tmp)->getAttr() & FINAL_A) == 0)
		{
			CONST_CONTROL_(tmp)
			TRY_DELETE(tmp);
			tmp = generatePrimitive(value);
			if(dynamic_cast<Reference *>(*dataPointer))
			{

				*dynamic_cast<Reference *>(*dataPointer)->getSlot() = tmp;
			}
			else
			{
				*dataPointer = tmp;
			}
		}
		else
		{
			(tmp)->setFromValue(value);
		}
	}
	else
	{
		throw Exception("Slot is empty");
	}
}

void Slot::toReference(Data **data)
{
	if(*dataPointer)
	{
		if(((*dataPointer)->getAttr() & FINAL_A) == 0 or dynamic_cast<Reference *>(*dataPointer))
		{
			CONST_CONTROL_(*dataPointer)
			TRY_DELETE(*dataPointer);
			*dataPointer = new Reference(data);
		}
		else
		{
			throw Exception("Data is marked final. It can not change its type");
		}
	}
	else
	{
		throw Exception("Slot is empty");
	}
}

void Slot::toReference(string value)
{
	if(*dataPointer)
	{
		if(((*dataPointer)->getAttr() & FINAL_A) == 0 or dynamic_cast<Reference *>(*dataPointer))
		{
			CONST_CONTROL_(*dataPointer)
			TRY_DELETE(*dataPointer);
			if(value.size())
				*dataPointer = new Reference(value);
			else
				*dataPointer = new Reference();
		}
		else
		{
			throw Exception("Data is marked final. It can not change its type");
		}
	}
	else
	{
		throw Exception("Slot is empty");
	}
}
/*
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
*/
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


Data *Slot::generatePrimitive(string value)
{
	if(Integer::is(value))
		return new Integer(atoi(value.c_str()));
	else if(Float::is(value))
		return new Float(atof(value.c_str()));
	else if(Bool::is(value))
		return new Bool(value == "true");
	else
		return new String(value);
}

Data **Slot::generateSlotPrimitive(string value)
{
	if(Integer::is(value))
		return new Data*(new Integer(atoi(value.c_str())));
	else if(Float::is(value))
		return new Data*(new Float(atof(value.c_str())));
	else if(Bool::is(value))
		return new Data*(new Bool(value == "true"));
	else
		return new Data*(new String(value));
}
