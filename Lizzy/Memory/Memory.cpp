#include "Memory.hpp"

using namespace Lizzy;


Memory::Memory(Memory *parent, string id) : unordered_map<string, Data *>(), self(*this), parent(parent), id(id)
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

Memory *Memory::getDownMemory()
{
	Memory *memory = this;
	while(memory->child)
	{
		memory = memory->child;
	}
	return memory;
}

void Memory::push(string id)
{
	Memory *memory = getDownMemory();
	memory->child = new Memory(memory, id);
}

void Memory::pop()
{
	Memory *memory = getDownMemory()->parent;
	if(memory)
	{
		delete memory->child;
		memory->child = nullptr;
	}
}

bool Memory::exists(string id)
{
	return find(id) != end();
}


bool Memory::existsGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		if(memory->exists(id)) return true;
		memory = memory->parent;
	}
	return false;
}

Data *Memory::getDataGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		if(memory->find(id) != memory->end()) return (*memory)[id];
		memory = memory->parent;
	}
	throw Exception(id + " Memory not exists");
}

void Memory::setAttr(string id, int attr)
{
	getDataGlobalUp(id)->setAttr(attr);
}

string Memory::getId()
{
	return id;
}

string Memory::getId(Data *d)
{
	Memory *memory = this;
	while(memory)
	{
		for(auto it : *memory) if(d == it.second) return it.first;
		memory = memory->parent;
	}
	throw Exception("Reference Memory is a reference to a Memory which not exists");
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
	return getDataGlobalUp(id)->dup();
}

void Memory::addPrimitiveData(string id, string value)
{
	if(not exists(id))
	{
		if(existsGlobalUp(value))
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

Integer *Memory::generateInteger(Data *reference)
{
	switch(reference->typeId())
	{
		case BOOL_T:
				return new Integer(((Bool *)reference)->get());
		case STRING_T:
			throw Exception(getId(reference) + " is String (can not convert String as Integer)");
		case VECTOR_T:
			throw Exception(getId(reference) + " is Vector (can not convert Vector as Integer)");
		case REFERENCE_T:
			throw Exception(getId(reference) + " is a reference to null");
		default:
			return new Integer(reference->toString());
	}
}

Integer *Memory::generateInteger(string value)
{
	if(existsGlobalUp(value))
	{
		return generateInteger(getDataGlobalUp(value));
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


Float *Memory::generateFloat(Data *reference)
{
	switch(reference->typeId())
	{
		case BOOL_T:
			return new Float(((Bool *)reference)->get());
		case STRING_T:
			throw Exception(getId(reference) + " is String (can not convert String as Float)");
		case VECTOR_T:
			throw Exception(getId(reference) + " is Vector (can not convert Vector as Float)");
		case REFERENCE_T:
			throw Exception(getId(reference) + " is a reference to null");
		default:
			return new Float(reference->toString());
	}
}

Float *Memory::generateFloat(string value)
{
	if(existsGlobalUp(value))
	{
		return generateFloat(getDataGlobalUp(value));
	}
	else
	{
		switch(type(value))
		{
			case BOOL_T:
				return new Float(value == "true");
			case STRING_T:
				throw Exception(value + " is String (can not convert String as Float)");
			default:
				return new Float(value);
		}
	}
}

Bool *Memory::generateBool(Data *reference)
{
	switch(reference->typeId())
	{
		case REFERENCE_T:
			throw Exception(getId(reference) + " is a reference to null");
		case VECTOR_T:
			throw Exception(getId(reference) + " is Vector (can not convert Vector as Bool)");
		case STRING_T:
			throw Exception(getId(reference) + " is String (can not convert String as Bool)");
		case INTEGER_T:
			return new Bool(((Integer *)reference)->get());
		case FLOAT_T:
			return new Bool(((Float *)reference)->get());
		default:
			return new Bool(reference->toString());
	}
}

Bool *Memory::generateBool(string value)
{
	if(existsGlobalUp(value))
	{
		return generateBool(getDataGlobalUp(value));
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
	if(existsGlobalUp(value))
	{
		return new String(getDataGlobalUp(value)->toString());
	}
	else
	{
		return new String(value);
	}
}

Reference *Memory::generateReference(string value)
{
	if(existsGlobalUp(value))
	{
		Data **data = getDataSlotGlobalUp(value);
		if(dynamic_cast<Reference *>(*data)) data = ((Reference *)*data)->getRef();
		return new Reference(data);
	}
	else
	{
		if(value.size() == 0)
			return new Reference(nullptr);
		throw Exception(value + " not exists");
	}
}


Vector *Memory::generateVector(vector<string>& values)
{
	Vector *data = new Vector();
	for(string value : values)
	{
		if(existsGlobalUp(value))
		{
			data->add(getDataGlobalUp(value)->dup());
		}
		else
		{
			data->add(generateDataFromValue(value));
		}
	}
	return data;
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


void Memory::addReference(string id, string value)
{
	if(not exists(id))
	{
		self[id] = generateReference(value);
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::addVector(string id, vector<string>& values)
{
	if(not exists(id))
	{
		self[id] = generateVector(values);
	}
	else
	{
		throw Exception(id +  " Memory already exists");
	}
}




void Memory::castInInteger(Integer *data, Data *reference)
{
	switch(reference->typeId())
	{
		case REFERENCE_T:
			if(((Reference *)reference)->get() == nullptr) throw Exception(getId(reference) + " is a reference to null");
			castInInteger(data, ((Reference *)reference)->get());
			break;
		case BOOL_T:
			data->set(((Bool *)reference)->get());
			break;
		case INTEGER_T:
			data->set(((Integer *)reference)->get());
			break;
		case FLOAT_T:
			data->set(((Float *)reference)->get());
			break;
		case STRING_T:
			throw Exception(getId(reference) + " is String (can not convert String as Integer)");
		default:;
	}		
}

void Memory::castInInteger(Integer *data, string value)
{
	if(existsGlobalUp(value))
	{
		castInInteger(data, getDataGlobalUp(value));
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
			default:;
		}
	}
}

void Memory::castInFloat(Float *data, Data *reference)
{
	switch(reference->typeId())
	{
		case REFERENCE_T:
			if(((Reference *)reference)->get() == nullptr) throw Exception(getId(reference) + " is a reference to null");
			castInFloat(data, ((Reference *)reference)->get());
		case BOOL_T:
			data->set(((Bool *)reference)->get());
			break;
		case INTEGER_T:
			data->set(((Integer *)reference)->get());
			break;
		case FLOAT_T:
			data->set(((Float *)reference)->get());
			break;
		case STRING_T:
			throw Exception(getId(reference) + " is String (can not convert String as Float)");
		default:;
	}	
}

void Memory::castInFloat(Float *data, string value)
{
	if(existsGlobalUp(value))
	{
		castInFloat(data, getDataGlobalUp(value));
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
				throw Exception(value + " is String (can not convert String as Float)");
			default:;
		}
	}
}

void Memory::castInBool(Bool *data, Data *reference)
{
	switch(reference->typeId())
	{
		case REFERENCE_T:
			if(((Reference *)reference)->get() == nullptr) throw Exception(getId(reference) + " is a reference to null");
			castInBool(data, ((Reference *)reference)->get());
		case BOOL_T:
			data->set(((Bool *)reference)->get());
			break;
		case INTEGER_T:
			data->set(((Integer *)reference)->get());
			break;
		case FLOAT_T:
			data->set(((Float *)reference)->get());
			break;
		case STRING_T:
			throw Exception(getId(reference) + " is String (can not convert String as Bool)");
		default:;
	}	
}


void Memory::castInBool(Bool *data, string value)
{
	if(existsGlobalUp(value))
	{
		 castInBool(data, getDataGlobalUp(value));
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
				throw Exception(value + " is String (can not convert String as Bool)");
			default:;
		}
	}
}


void Memory::castInString(String *data, string value)
{
	if(existsGlobalUp(value))
	{
		data->set(getDataGlobalUp(value)->toString());
	}
	else
	{
		data->set(value);
	}
}

void Memory::castInReference(Reference *ref, string value)
{
	castIn(ref->get(), value);
}


void Memory::castInVector(Vector *ref, string value)
{
	if(existsGlobalUp(value))
	{
		Data *data = getDataGlobalUp(value);
		if(data->typeId() == VECTOR_T)
		{
			Vector *vec = dynamic_cast<Vector *>(data);
			ref->copyVector(vec->getVector());
		}
		else
		{
			throw Exception("can not cast " + data->type() + " into Vector");
		}
	}
	else
	{
		throw Exception("can not cast " + inferType(value) + " into Vector");
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
		case REFERENCE_T: castInReference((Reference *)data, value); break;
		case VECTOR_T: castInVector((Vector *)data, value); break;
		default:;
	}
}

Data **Memory::getDataSlotGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		if(memory->exists(id)) return &(*memory)[id];
		memory = memory->parent;
	}
	throw Exception(id + " Memory not exists");
}

Data **Memory::inferReference(string id, string value)
{
	Data **data = getDataSlotGlobalUp(id);
	if(dynamic_cast<Reference *>(*data))
	{
		if(not ((Reference *)*data)->get())
		{
			throw Exception(id + " Reference is null");
		}
		else
		{
			data = ((Reference *)*data)->getRef();
		}
	}
	return data;
}

void Memory::setDataFromValue(string id, string value)
{
	Types tv = type(value);
	Data **data = inferReference(id, value);
	switch(attr_final_control(*data, tv))
	{
		case FORB:
			throw Exception(id + " is marked final, can not change his type (" + (*data)->type() + " into " + inferType(value) + ")");
		case CAST:
			castIn(*data, value);
			break;
		case FULL:
			delete *data;
			*data = generateDataFromValue(value);
	}
}

void Memory::setDataFromId(string id, string value)
{
	Types tv = getDataGlobalUp(value)->typeId();
	Data **data = inferReference(id, value);
	switch(attr_final_control(*data, tv))
	{
		case FORB:
			throw Exception(id + " is marked final, can not change his type (" + (*data)->type() + " into " + inferType(value) + ")");
		case CAST:
			castIn(*data, value);
			break;
		case FULL:
			delete *data;
			*data = generateDataFromId(value);
	}
}

void Memory::setData(string id, string value)
{
	if(existsGlobalUp(id))
	{
		if(existsGlobalUp(value))
			setDataFromId(id, value);
		else
			setDataFromValue(id, value);
	}
	else
	{
		throw Exception(id +  " Memory not exists");
	}
}

void Memory::setVectorAt(string id, string index, string value)
{
	if(existsGlobalUp(id))
	{
		Data *data = getDataGlobalUp(id);
		if(data->typeId() == VECTOR_T)
		{
			Vector *vec = dynamic_cast<Vector *>(data);
			int i = -1;
			if(existsGlobalUp(index))
			{
				Data *dataIndex = getDataGlobalUp(index);
				if(dataIndex->typeId() == INTEGER_T)
				{
					i = ((Integer *)dataIndex)->get();
				}
				else
				{
					throw Exception(index + " can not be interpreted as Vector index");
				}
			}
			else
			{
				i = atoi(index.c_str());
			}
			if(i < 0 or i >= vec->getVector().size())
			{
				throw Exception("index out of band of size of Vector");
			}
			if(existsGlobalUp(value))
			{
				vec->getVector()[i] = generateDataFromId(value);
			}
			else
			{
				vec->getVector()[i] = generateDataFromValue(value);
			}
		}
		else
		{
			throw Exception(id + " is not a Vector");
		}
	}
	else
	{
		throw Exception(id + " Memory not exists");
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
	Data *data = getDataGlobalUp(id);
	return data->toString();
}

string Memory::getType(string id)
{
	Data *data = getDataGlobalUp(id);
	return data->type();
}

void Memory::changeReference(string id, string value)
{
	if(existsGlobalUp(value))
	{

		switch(attr_final_control(getDataGlobalUp(id), getDataGlobalUp(value)->typeId(), true))
		{
			case FORB:
				throw Exception(id + " is marked final, can not change his reference type (" + getDataGlobalUp(id)->type() + " into " + inferType(value) + ")");
			case CAST:
			case FULL:
				((Reference *)getDataGlobalUp(id))->set(getDataSlotGlobalUp(value));

		}
	}
	else
	{
		throw Exception("can not set reference to " + value + ", because it not exists");
	}
}

string Memory::new_primitive(string id, string value)
{
	getDownMemory()->addPrimitiveData(id, value);
	return id;
}

string Memory::new_Integer(string id, string value)
{
	getDownMemory()->addInteger(id, value);
	return id;
}

string Memory::new_Float(string id, string value)
{
	getDownMemory()->addFloat(id, value);
	return id;
}

string Memory::new_Bool(string id, string value)
{
	getDownMemory()->addBool(id, value);
	return id;
}

string Memory::new_String(string id, string value)
{
	getDownMemory()->addString(id, value);
	return id;
}

string Memory::new_Reference(string id, string value)
{
	getDownMemory()->addReference(id, value);
	return id;
}

string Memory::new_Vector(string id, vector<string>& values)
{
	getDownMemory()->addVector(id, values);
	return id;
}

string Memory::set_memory(string id, string value)
{
	Memory *memory = getDownMemory();
	memory->attr_const_control(id);
	memory->setData(id, value);
	return id;
}

string Memory::set_at(string id, string index, string value)
{
	Memory *memory = getDownMemory();
	memory->attr_const_control(id);
	memory->setVectorAt(id, index, value);
	return id;
}

string Memory::set_reference(string id, string value)
{
	Memory *memory = getDownMemory();
	memory->attr_const_control(id, true);
	memory->changeReference(id, value);
	return id;
}

string Memory::get_memory(string id)
{
	return getDownMemory()->toString(id);
}

string Memory::type_memory(string id)
{
	Memory *memory = getDownMemory();
	if(memory->existsGlobalUp(id))
	{
		return memory->getDataGlobalUp(id)->type();
	}
	return Memory::inferType(id);
}

string Memory::exists_memory(string id)
{
	return getDownMemory()->existsGlobalUp(id) ? "true" : "false";
}


void Memory::attr_const_control(string id, bool refmode)
{
	if(existsGlobalUp(id))
	{
		Data *data = getDataGlobalUp(id);
		int attr = refmode ? ((Reference *)data)->getRefAttr() : data->getAttr();
		if(attr & CONST_A) throw Exception(id + " is marked const, it can not be modified");
	}
}

string Memory::add_attribute(string id, int attr)
{
	getDownMemory()->addAttr(getDownMemory()->getDataGlobalUp(id), attr);
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
	return otherType == REFERENCE_T or otherType == INTEGER_T or otherType == FLOAT_T or otherType == BOOL_T;
}

bool Memory::isAllowedStringFrom(Types otherType)
{
	return otherType == REFERENCE_T or otherType == INTEGER_T or otherType == FLOAT_T or otherType == BOOL_T or otherType == STRING_T;
}

bool Memory::isAllowedTypeFrom(Types t1, Types t2)
{
	switch(t1)
	{
		case INTEGER_T: case FLOAT_T: case BOOL_T: return isAllowedNumberFrom(t2);
		case VECTOR_T: return t2 == VECTOR_T;
		case STRING_T: default: return isAllowedStringFrom(t2);
	}
	return true;
}


SetModes Memory::attr_final_control(Data *data, Types otherType, bool refmode)
{
	if((refmode ? ((Reference *)data)->getRefAttr() : data->getAttr()) & FINAL_A)
	{
		if(isAllowedTypeFrom(data->typeId(), otherType)) return CAST;
		return FORB;
	}
	return FULL;
}
