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

void Memory::setAttr(string id, const DataAttributes& attr)
{
	getData(id)->setAttr(attr);
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
 /* TO FINISH */
Integer *Memory::generateInteger(string value)
{
	if(exists(value))
	{
		switch(self[value]->typeId())
		{
			case BOOL_T:
				return new Integer(((Bool *)self[value])->get());
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
			default:
				return new Integer(self[value]->toString());
		}
	}
	else
	{
		switch(type(value))
		{
			case BOOL_T:
				return new Integer(value == "true");
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
			default:
				return new Integer(value);
		}
	}
}

Float *Memory::generateFloat(string value)
{
	if(exists(value))
	{
		switch(self[value]->typeId())
		{
			case BOOL_T:
				return new Float(((Bool *)self[value])->get());
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Float)");
			default:
				return new Float(self[value]->toString());
		}
	}
	else
	{
		switch(type(value))
		{
			case BOOL_T:
				return new Float(value == "true");
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Float)");
			default:
				return new Float(value);
		}
	}
}

Bool *Memory::generateBool(string value)
{
	if(exists(value))
	{
		switch(self[value]->typeId())
		{
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Bool)");
			case INTEGER_T:
				return new Bool(((Integer *)self[value])->get());
				break;
			case FLOAT_T:
				return new Bool(((Float *)self[value])->get());
				break;
			default:
				return new Bool(self[value]->toString());
		}
	}
	else
	{
		switch(type(value))
		{
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Bool)");
			case INTEGER_T:
				return new Bool(atoi(value.c_str()));
				break;
			case FLOAT_T:
				return new Bool(atof(value.c_str()));
				break;
			default:
				return new Bool(value);
		}
	}
}

String *Memory::generateString(string value)
{
	if(exists(value))
	{
		return new String(self[value]->toString());
	}
	else
	{
		return new String(value);
	}
}

void Memory::addInteger(string id, string value)
{
	if(not exists(id))
	{
		self[id] = generateInteger(value);
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::addFloat(string id, string value)
{
	if(not exists(id))
	{
		self[id] = generateFloat(value);
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::addBool(string id, string value)
{
	if(not exists(id))
	{
		self[id] = generateBool(value);
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::addString(string id, string value)
{
	if(not exists(id))
	{
		self[id] = generateString(value);
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

string Memory::new_Integer(string id, string value)
{
	addInteger(id, value);
	return id;
}

string Memory::new_Float(string id, string value)
{
	addFloat(id, value);
	return id;
}

string Memory::new_Bool(string id, string value)
{
	addBool(id, value);
	return id;
}

string Memory::new_String(string id, string value)
{
	addString(id, value);
	return id;
}

string Memory::new_primitive(string id, string value, const DataAttributes& attr)
{
	addPrimitiveData(id, value);
	setAttr(id, attr);
	return id;
}

string Memory::new_Integer(string id, string value, const DataAttributes& attr)
{
	addInteger(id, value);
	setAttr(id, attr);
	return id;
}

string Memory::new_Float(string id, string value, const DataAttributes& attr)
{
	addFloat(id, value);
	setAttr(id, attr);
	return id;
}

string Memory::new_Bool(string id, string value, const DataAttributes& attr)
{
	addBool(id, value);
	setAttr(id, attr);
	return id;
}

string Memory::new_String(string id, string value, const DataAttributes& attr)
{
	addString(id, value);
	setAttr(id, attr);
	return id;
}



string Memory::set_memory(string id, string value)
{
	/*
	
	AMELIORER!!!

	*/
	WR_CONTROL(id);
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



void Memory::WR_CONTROL(string id)
{
	if(exists(id))
	{
		Data *data = self[id];
		if(data->getAttr()._const) throw Exception(id + " is marked const, it can not be modified");
	}
}

Data *&Memory::RD(const string& key)
{
	return self[key];
}

Data *&Memory::WR(const string& key)
{
	return self[key];
}

