#include "Memory.hpp"

using namespace Lizzy;


Memory::Memory() : unordered_map<string, Data *>(), self(*this)
{
	cout << "Memory created" << endl;
}

Memory::~Memory()
{
	for(auto it : *this)
	{
		cout << it.second->type() << " deleted" << endl;
		delete it.second;
	}
	cout << "Memory deleted" << endl;
}

bool Memory::exists(string id)
{
	return find(id) != end();
}

void Memory::addIntegerData(string id, string stri)
{
	Integer *integer = new Integer(stri);
	self[id] = integer;
}

void Memory::addFloatData(string id, string strf)
{
	Float *floatd = new Float(strf);
	self[id] = floatd;
}

void Memory::addBoolData(string id, string strb)
{
	Bool *boolean = new Bool(strb);
	self[id] = boolean;
}

void Memory::addStringData(string id, string strs)
{
	String *stringd = new String(strs);
	self[id] = stringd;
}

Data *Memory::generateCopyOf(string id)
{
	return getData(id)->dup();
}

void Memory::addCopyData(string id, string cpId)
{
	self[id] = generateCopyOf(cpId);
}

void Memory::addPrimitiveData(string id, string strGenValue)
{
	if(not exists(id))
	{
		if(exists(strGenValue))
		{
			addCopyData(id, strGenValue);
		}
		else
		{
			switch(type(strGenValue)) //constante littérales
			{
				case INTEGER_T: addIntegerData(id, strGenValue); break;
				case FLOAT_T: addFloatData(id, strGenValue); break;
				case BOOL_T: addBoolData(id, strGenValue); break;
				case STRING_T: addStringData(id, strGenValue); break;
				default: throw Exception("Uknown type has been occured");
			}
		}
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::setData(string id, string strGenValue)
{
	if(exists(id))
	{
		
	}
	else
	{
		throw Exception(id +  " Memory not exists");
	}
}


Data *Memory::getData(string id)
{
	if(exists(id)) return self[id];
	throw Exception(id + " Memory does not exists");
}

Types Memory::type(string constStrGenValue)
{
	if(Integer::is(constStrGenValue)) return INTEGER_T;
	if(Float::is(constStrGenValue)) return FLOAT_T;
	if(Bool::is(constStrGenValue)) return BOOL_T;
	return STRING_T;
}

string Memory::inferType(string constStrGenValue)
{
	if(Integer::is(constStrGenValue)) return "Integer";
	if(Float::is(constStrGenValue)) return "Float";
	if(Bool::is(constStrGenValue)) return "Bool";
	return "String";
}


string Memory::toString(string id)
{
	Data *data = getData(id);
	return data->toString();
}

string Memory::getType(string id)
{
	Data *data = getData(id);
	return data->type();
}


string Memory::new_primitive(string id, string value)
{
	addPrimitiveData(id, value);
	return "null";
}