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

vector<string> Memory::toAccessor(string id)
{
	return cmd::String(id).split_std(".");
}

bool Memory::isAccessor(string id)
{
	return toAccessor(id).size() > 1;
}

bool Memory::isAccessor(Data *data)
{
	return data->typeId() == VECTOR_T or data->typeId() == TABLE_T or data->typeId() == OBJECT_T;
}

bool Memory::exists(string id)
{
	if(find(id) != end()) return true;
	auto accessor = toAccessor(id);
	if(accessor.size() > 1)
	{
		if(find(accessor[0]) != end())
		{
			Data *data = getDataGlobalUp(accessor[0]);
			if(isAccessor(data))
			{
				return true;
			}
		}
	}
	return false;
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

Data *Memory::getDataFromAccessor(string expr)
{
	auto accessor = toAccessor(expr);
	auto len = accessor.size();
	if(len > 1)
	{
		Data *data = getDataGlobalUp(accessor[0]);
		for(int i = 1; i < len; i++)
		{
			Data *elem = nullptr;
			int j = 0;
			if(existsGlobalUp(accessor[i]))
			{
				 elem = getDataGlobalUp(accessor[i]);
				 if(elem)
				 {
				 	if(elem->typeId() == INTEGER_T)
				 	{
				 		j = dynamic_cast<Integer *>(elem)->get();
				 	}
				 	else
				 	{
				 		throw Exception(getId(elem) + " is " + elem->type() + ", it can not be interpreted as an accessor index");
				 	}
				 }
			}
			else
			{
				if(type(accessor[i]) == INTEGER_T)
				{
					j = atoi(accessor[i].c_str());
				}
				else
				{
					throw Exception(accessor[i] + " is " + inferType(accessor[i]) + ", it can not be interpreted as an accessor index");
				}
			}
			switch(data->typeId())
			{
				case VECTOR_T:
					if(dynamic_cast<Reference *>(data)) data = dynamic_cast<Reference *>(data)->get();
					if(j < 0 or j >= dynamic_cast<Vector *>(data)->getVector().size())
						throw Exception(to_string(j) + " is out ouf band of the size of vector");
					data = dynamic_cast<Vector *>(data)->getVector()[j];
					break;
				default:
					throw Exception(expr + " try to access to a non accessible data type: " + data->type());
			}
		}
		return data;
	}
	throw Exception(expr + " does not represents an accessor expression");
}


Data **Memory::getDataSlotFromAccessor(string expr)
{
	auto accessor = toAccessor(expr);
	auto len = accessor.size();
	if(len > 1)
	{
		Data **data = getDataSlotGlobalUp(accessor[0]);
		for(int i = 1; i < len; i++)
		{
			Data **elem = nullptr;
			int j = 0;
			if(existsGlobalUp(accessor[i]))
			{
				 elem = getDataSlotGlobalUp(accessor[i]);
				 if(*elem)
				 {
				 	if((*elem)->typeId() == INTEGER_T)
				 	{
				 		j = dynamic_cast<Integer *>(*elem)->get();
				 	}
				 	else
				 	{
				 		throw Exception(getId(*elem) + " is " + (*elem)->type() + ", it can not be interpreted as an accessor index");
				 	}
				 }
			}
			else
			{
				if(type(accessor[i]) == INTEGER_T)
				{
					j = atoi(accessor[i].c_str());
				}
				else
				{
					throw Exception(accessor[i] + " is " + inferType(accessor[i]) + ", it can not be interpreted as an accessor index");
				}
			}
			switch((*data)->typeId())
			{
				case VECTOR_T:
					if(dynamic_cast<Reference *>(*data)) data = dynamic_cast<Reference *>(*data)->getRef();
					if(j < 0 or j >= dynamic_cast<Vector *>(*data)->getVector().size())
						throw Exception(to_string(j) + " is out ouf band of the size of vector");
					data = &dynamic_cast<Vector *>(*data)->getVector()[j];
					break;
				default:
					throw Exception(expr + " try to access to a non accessible data type: " + (*data)->type());
			}
		}
		return data;
	}
	throw Exception(expr + " does not represents an accessor expression");
}


Data *Memory::getDataGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		if(memory->find(id) != memory->end())
		{
			 return (*memory)[id];
		}
		else
		{
			if(isAccessor(id))
			{
				return getDataFromAccessor(id);
			}
		}
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
		if((*data)->getAttr() & RESTRICT_A) throw Exception(value + " is marked 'restrict', it can not be referenced");
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
		if(memory->exists(id))
		{
			if(memory->find(id) != memory->end())
			{
				 return &(*memory)[id];
			}
			else if(memory->isAccessor(id))
			{
				return getDataSlotFromAccessor(id);
			}
		}
		memory = memory->parent;
	}
	throw Exception(id + " Memory not exists");
}

Data **Memory::inferReference(string id)
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
	Data **data = inferReference(id);
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
	Data **data = inferReference(id);
	Data *valueptr = nullptr;
	switch(attr_final_control(*data, tv))
	{
		case FORB:
			throw Exception(id + " is marked final, can not change his type (" + (*data)->type() + " into " + inferType(value) + ")");
		case CAST:
			castIn(*data, value);
			break;
		case FULL:
			valueptr = generateDataFromId(value);
			delete *data;
			*data = valueptr;
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
		Data **slot = nullptr;
		Data *ref = getDataGlobalUp(id);
		if(dynamic_cast<Reference *>(ref))
		{
			switch(attr_final_control(ref, getDataGlobalUp(value)->typeId(), true))
			{
				case FORB:
					throw Exception(id + " is marked final, can not change his reference type (" + getDataGlobalUp(id)->type() + " into " + inferType(value) + ")");
				case CAST:
				case FULL:
					slot = getDataSlotGlobalUp(value);
					if((*slot)->getAttr() & RESTRICT_A) throw Exception(value + " is marked 'restrict', it can not be referenced");
					((Reference *)ref)->set(slot);
			}
		}
		else
		{
			throw Exception(id + " is not a Reference");
		}
	}
	else
	{
		throw Exception("can not set reference to " + value + ", because it not exists");
	}
}

void Memory::toReference(string id, string value)
{
	Data **ref = getDataSlotGlobalUp(id);
	switch(attr_final_control(*ref, REFERENCE_T))
	{
		case FORB:
		case CAST:
			throw Exception(id + " is marked final, can not change his reference type (" + getDataGlobalUp(id)->type() + " into " + inferType(value) + ")");
		case FULL:
			delete *ref;
			*ref = generateReference(value);
	}
}

string Memory::getCharAt(string id, string index)
{
	String *str = dynamic_cast<String *>(*inferReference(id));
	if(not str)
		throw Exception(id + " is not a String");
	if(type(index) == STRING_T)
	{
		Integer *indexd = dynamic_cast<Integer *>(getDataGlobalUp(index));
		if(indexd)
		{
			if(indexd->get() >= 0 and indexd->get() < str->get().size())
			{
				return string(1, str->get()[indexd->get()]);
			}
			throw Exception("index out of band");
		}
	}
	else
	{
		if(Integer::is(index))
		{
			int i = atoi(index.c_str());
			if(i >= 0 and i < str->get().size())
			{
				return string(1, str->get()[i]);
			}
			throw Exception("index out of band");
		}
	}
	throw Exception(index + " can not be interpreted as a String index");
}

void Memory::setCharAt(string id, string index, string character)
{
	if(character.size() > 1) throw Exception(character + " is String, expected character");
	String *str = dynamic_cast<String *>(*inferReference(id));
	if(not str)
		throw Exception(id + " is not a String");
	if(type(index) == STRING_T)
	{
		Integer *indexd = dynamic_cast<Integer *>(getDataGlobalUp(index));
		if(indexd)
		{
			if(indexd->get() >= 0 and indexd->get() < str->get().size())
			{
				(*str)[indexd->get()] = character[0];
				return;
			}
			throw Exception("index out of band");
		}
	}
	else
	{
		if(Integer::is(index))
		{
			int i = atoi(index.c_str());
			if(i >= 0 and i < str->get().size())
			{
				(*str)[i] = character[0];
				return;
			}
			throw Exception("index out of band");
		}
	}
	throw Exception(index + " can not be interpreted as a String index");
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

string Memory::set_reference(string id, string value)
{
	Memory *memory = getDownMemory();
	memory->attr_const_control(id, true);
	memory->changeReference(id, value);
	return id;
}

string Memory::to_reference(string id, string value)
{
	Memory *memory = getDownMemory();
	memory->attr_const_control(id);
	memory->toReference(id, value);
	return id;
}

int Memory::getVectorSize(string id)
{
	Vector *vec = dynamic_cast<Vector *>(getDataGlobalUp(id));
	if(not vec)
		throw Exception(id + " is not a Vector; it is " + inferType(id));
	return vec->getVector().size();
}

string Memory::get_memory(string id)
{
	return getDownMemory()->toString(id);
}


string Memory::size_vector(string id)
{
	return to_string(getDownMemory()->getVectorSize(id));
}


string Memory::get_char_at(string id, string index)
{
	return getDownMemory()->getCharAt(id, index);
}

string Memory::set_char_at(string id, string index, string character)
{
	Memory *memory = getDownMemory();
	memory->attr_const_control(id);
	memory->setCharAt(id, index, character);
	return id;
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
