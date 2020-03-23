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

void Memory::setIntegerData(string id, string stri)
{
	if(self[id]->typeId() == INTEGER_T)
	{
		((Integer *)self[id])->set(atoi(stri.c_str()));
	}
	else
	{
		delete self[id];
		addIntegerData(id, stri);
	}
}

void Memory::setFloatData(string id, string strf)
{
	if(self[id]->typeId() == FLOAT_T)
	{
		((Float *)self[id])->set(atof(strf.c_str()));
	}
	else
	{
		delete self[id];
		addFloatData(id, strf);
	}
}

void Memory::setBoolData(string id, string strb)
{
	if(self[id]->typeId() == BOOL_T)
	{
		((Bool *)self[id])->set(strb == "true");
	}
	else
	{
		delete self[id];
		addBoolData(id, strb);
	}
}

void Memory::setStringData(string id, string strs)
{
	if(self[id]->typeId() == STRING_T)
	{
		((String *)self[id])->set(strs);
	}
	else
	{
		delete self[id];
		addStringData(id, strs);
	}
}

void Memory::setCopyData(string id, string cpId)
{
	if(self[id]->typeId() == self[cpId]->typeId())
	{
		switch(self[id]->typeId())
		{
			case INTEGER_T: *(Integer *)self[id] = *(Integer *)self[cpId]; break;
			case FLOAT_T: *(Float *)self[id] = *(Float *)self[cpId]; break;
			case BOOL_T: *(Bool *)self[id] = *(Bool *)self[cpId]; break;
			case STRING_T: *(String *)self[id] = *(String *)self[cpId]; break;
			default: throw Exception("Uknown type has been occured");
		}
	}
	else
	{
		delete self[id];
		addCopyData(id, cpId);
	}
}


void Memory::setData(string id, string value)
{
	if(exists(id))
	{
		if(exists(value))
		{
			setCopyData(id, value);
		}
		else
		{
			switch(type(value)) //constante littérales
			{
				case INTEGER_T: setIntegerData(id, value); break;
				case FLOAT_T: setFloatData(id, value); break;
				case BOOL_T: setBoolData(id, value); break;
				case STRING_T: setStringData(id, value); break;
				default: throw Exception("Uknown type has been occured");
			}
		}
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
	return id;
}

string Memory::set_memory(string id, string value)
{
	setData(id, value);
	return id;
}

string Memory::get_memory(string id)
{
	return toString(id);
}

string Memory::value_type_memory(string value)
{
	return Memory::inferType(value);
}


string Memory::data_type_memory(string id)
{
	return getData(id)->type();
}

