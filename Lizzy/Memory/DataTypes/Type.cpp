#include "Type.hpp"

using namespace Lizzy;


Types Type::type(string constStrGenValue)
{
	if(Integer::is(constStrGenValue)) return INTEGER_T;
	if(Float::is(constStrGenValue)) return FLOAT_T;
	if(Bool::is(constStrGenValue)) return BOOL_T;
	return STRING_T;
}

string Type::inferType(string constStrGenValue)
{
	if(Integer::is(constStrGenValue)) return "Integer";
	if(Float::is(constStrGenValue)) return "Float";
	if(Bool::is(constStrGenValue)) return "Bool";
	return "String";
}

Data **Type::generateSlot(Data *data)
{
	return new Data*(data);
}

Data *Type::generatePrimitive(string value)
{
	if(Integer::is(value))
		return new Integer(atoi(value.c_str()));
	if(Float::is(value))
		return new Float(atof(value.c_str()));
	if(Bool::is(value))
		return new Bool(value == "true");
	return new String(value);
}


void Type::updateSlot(Slot *slot, string value)
{
	if(not slot->isFinal())
	{
		if(not slot->isConst())
		{
			delete *slot->get();
			*slot->get() = generatePrimitive(value);
		}
		else
		{
			throw Exception("Data is marked const, it can not be modified");
		}
	}
	else
	{
		(*slot->get())->setFromValue(value);
	}
}

void Type::updateSlot(Slot *slot, Data *data)
{
	if(*slot->get() == data)
	{
		throw Exception("Can not modify Data with its own value");
	}
	if(not slot->isFinal())
	{
		if(not slot->isConst())
		{
			delete *slot->get();
			*slot->get() = data->dup();
		}
		else
		{
			throw Exception("Data is marked const, it can not be modified");
		}
	}
	else
	{
		(*slot->get())->setFromData(data);
	}
}

long Type::extractIndex(Slot *slot)
{
	Data *data = *slot->get();
	if(dynamic_cast<Integer *>(data))
		return dynamic_cast<Integer *>(data)->get();
	if(dynamic_cast<Float *>(data))
		return (long)dynamic_cast<Float *>(data)->get();
	if(dynamic_cast<Bool *>(data))
		return (long)dynamic_cast<Bool *>(data)->get();
	throw Exception("can not extract index from " + data->type());
}

long Type::extractIndex(string value)
{
	if(Integer::is(value))
		return atoi(value.c_str());
	if(Float::is(value))
		return (long)atof(value.c_str());
	if(Bool::is(value))
		return (long)(value == "true");
	throw Exception("can not extract index from " + inferType(value));
}


void Type::setField(Slot *tableSlot, string fieldname, Slot *value)
{
	Table *tableData = dynamic_cast<Table *>(*tableSlot->get());
	auto& table = tableData->getTable();
	if(not tableSlot->isConst())
	{
		tableData->setField(fieldname, value);
	}
	else
	{
		throw Exception("Table is marked const, can not set new field");
	}
}
