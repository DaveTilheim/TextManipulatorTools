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

Data *Memory::generateDataFromValue(string value)
{
	switch(type(value)) //constante littérales
	{
		case INTEGER_T: return new Integer(value);
		case FLOAT_T: return new Float(value);
		case BOOL_T: return new Bool(value);
		case STRING_T: return new String(value);
		default: throw Exception("Uknown type has been occured");
	}
}

Data *Memory::generateDataFromId(string id)
{
	return getData(id)->dup();
}

void Memory::addPrimitiveData(string id, string value)
{
	if(not exists(id))
	{
		if(exists(value))
		{
			self[id] = generateDataFromId(value);
		}
		else
		{
			self[id] = generateDataFromValue(value);
		}
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::setDataFromValue(string id, string value)
{
	auto tv = type(value);
	if(self[id]->typeId() == tv)
	{
		switch(tv) //constante littérale
		{
			case INTEGER_T: ((Integer *)self[id])->set(atoi(value.c_str())); break;
			case FLOAT_T: return ((Float *)self[id])->set(atof(value.c_str())); break;
			case BOOL_T: return ((Bool *)self[id])->set(value == "true"); break;
			case STRING_T: return ((String *)self[id])->set(value); break;
			default: throw Exception("Uknown type has been occured");
		}
	}
	else
	{
		delete self[id];
		self[id] = generateDataFromValue(value);
	}
}

void Memory::setDataFromId(string id, string cpId)
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
		self[id] = generateDataFromId(cpId);
	}
}

void Memory::setData(string id, string value)
{
	if(exists(id))
	{
		if(exists(value))
		{
			setDataFromId(id, value);
		}
		else
		{
			setDataFromValue(id, value);
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

