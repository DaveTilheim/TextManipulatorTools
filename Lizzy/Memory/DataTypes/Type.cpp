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


void Type::updateSlot(Data **slot, string value)
{
	if(((*slot)->getAttr() & FINAL_A) == 0)
	{
		CONST_CONTROL_(*slot);
		delete *slot;
		*slot = generatePrimitive(value);
	}
	else
	{
		(*slot)->setFromValue(value);
	}
}

void Type::updateSlot(Data **slot, Data *data)
{
	if(((*slot)->getAttr() & FINAL_A) == 0)
	{
		CONST_CONTROL_(*slot);
		delete *slot;
		*slot = data->dup();
	}
	else
	{
		(*slot)->setFromData(data);
	}
}




