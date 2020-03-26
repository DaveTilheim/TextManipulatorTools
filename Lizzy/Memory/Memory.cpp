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

void Memory::setAttr(string id, int attr)
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





void Memory::castInInteger(Integer *data, string value)
{
	if(exists(value))
	{
		switch(self[value]->typeId())
		{
			case BOOL_T:
				data->set(((Bool *)self[value])->get());
				break;
			case INTEGER_T:
				data->set(((Integer *)self[value])->get());
				break;
			case FLOAT_T:
				data->set(((Float *)self[value])->get());
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
		}
	}
	else
	{
		switch(type(value))
		{
			case BOOL_T:
				data->set(value == "true");
				break;
			case INTEGER_T:
			case FLOAT_T:
				data->set(atoi(value.c_str()));
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
		}
	}
}

void Memory::castInFloat(Float *data, string value)
{
	if(exists(value))
	{
		switch(self[value]->typeId())
		{
			case BOOL_T:
				data->set(((Bool *)self[value])->get());
				break;
			case INTEGER_T:
				data->set(((Integer *)self[value])->get());
				break;
			case FLOAT_T:
				data->set(((Float *)self[value])->get());
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
		}
	}
	else
	{
		switch(type(value))
		{
			case BOOL_T:
				data->set(value == "true");
				break;
			case INTEGER_T:
			case FLOAT_T:
				data->set(atof(value.c_str()));
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
		}
	}
}

void Memory::castInBool(Bool *data, string value)
{
	if(exists(value))
	{
		switch(self[value]->typeId())
		{
			case BOOL_T:
				data->set(((Bool *)self[value])->get());
				break;
			case INTEGER_T:
				data->set(((Integer *)self[value])->get());
				break;
			case FLOAT_T:
				data->set(((Float *)self[value])->get());
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
		}
	}
	else
	{
		switch(type(value))
		{
			case BOOL_T:
				data->set(value == "true");
				break;
			case INTEGER_T:
			case FLOAT_T:
				data->set(atof(value.c_str()));
				break;
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Integer)");
		}
	}
}


void Memory::castInString(String *data, string value)
{
	if(exists(value))
	{
		data->set(self[value]->toString());
	}
	else
	{
		data->set(value);
	}
}

void Memory::castIn(Data *data, string value)
{
	switch(data->typeId())
	{
		case INTEGER_T: castInInteger((Integer *)data, value); break;
		case FLOAT_T: castInFloat((Float *)data, value); break;
		case BOOL_T: castInBool((Bool *)data, value); break;
		case STRING_T: castInString((String *)data, value); break;
	}
}

void Memory::setDataFromValue(string id, string value)
{
	Types tv = type(value);
	switch(attr_final_control(self[id], tv))
	{
		case FORB:
			throw Exception(id + " is marked final, can not change his type (" + self[id]->type() + " into " + inferType(value) + ")");
		case CAST:
			castIn(self[id], value);
			break;
		case FULL:
			delete self[id];
			self[id] = generateDataFromValue(value);
	}
}

void Memory::setData(string id, string value)
{
	if(exists(id))
	{
		setDataFromValue(id, value);
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

string Memory::set_memory(string id, string value)
{
	attr_const_control(id);
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



void Memory::attr_const_control(string id)
{
	if(exists(id))
	{
		Data *data = self[id];
		if(data->getAttr() & CONST_A) throw Exception(id + " is marked const, it can not be modified");
	}
}

string Memory::add_attribute(string id, int attr)
{
	addAttr(getData(id), attr);
	return id;
}

void Memory::attr_set_control(Data *data, int attr)
{
	if(data->getAttr() & attr) throw Exception(getAttrAsString(attr) + " attribute is already set");
}

void Memory::addAttr(Data *data, int attr)
{
	attr_set_control(data, attr);
	data->setAttr(data->getAttr() | attr);
}

bool Memory::isAllowedNumberFrom(Types otherType)
{
	return otherType == INTEGER_T or otherType == FLOAT_T or otherType == BOOL_T;
}

bool Memory::isAllowedStringFrom(Types otherType)
{
	return otherType == INTEGER_T or otherType == FLOAT_T or otherType == BOOL_T or otherType == STRING_T;
}

bool Memory::isAllowedTypeFrom(Types t1, Types t2)
{
	switch(t1)
	{
		case INTEGER_T: case FLOAT_T: case BOOL_T: return isAllowedNumberFrom(t2);
		case STRING_T: default: return isAllowedStringFrom(t2);
	}
}


SetModes Memory::attr_final_control(Data *data, Types otherType)
{
	if(data->getAttr() & FINAL_A)
	{
		if(isAllowedTypeFrom(data->typeId(), otherType)) return CAST;
		return FORB;
	}
	return FULL;
}
