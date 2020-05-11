#include "Memory.hpp"

using namespace Lizzy;

PersistantMemory Memory::persistant = PersistantMemory();


Memory::Memory(Memory *parent, string id) : parent(parent), id(id), references(), stack()
{
	cout << "Memory created" << endl;
}

Memory::~Memory()
{
	for(auto it : stack)
	{
		cout << it.first << endl;
		TRY_SLOT_DELETE(it.second);
	}
	stack.clear();
	references.clear();
	cout << "Memory deleted" << endl;
}


void Memory::traceMemory()
{
	Memory *memory = getUpMemory();
	int i = 0;
	while(memory)
	{
		for(auto it : memory->stack)
		{
			cout << "[ " + it.first + " | ";
			cout << it.second << " | " + (*it.second)->type() + "(" + (*it.second)->toString() + ") ]" << endl;
		}
		memory = memory->child;
		i++;
	}
}


Data **Memory::getPersistantDataSlot(Data *data)
{
	Reference::StrictInfer(&data);
	auto len = persistant.size();
	for(int i = 0; i < len ; i++)
	{
		if(data == *persistant[i]) return persistant[i];
	}
	throw Exception("Data is not persistant");
}

void Memory::erasePersistantMemory()
{
	for(Data **slot : persistant)
	{
		delete *slot;
		delete slot;
	}
}


Data **Memory::findStack(string id)
{
	return stack.find(id) == stack.end() ? nullptr : stack[id];
}

Data **Memory::find(string id)
{
	Data **slot = findStack(id);
	if(slot) return slot;
	if(references.find(id) != references.end())
		return findStack(references[id]);
	return nullptr;
}



Memory *Memory::getMemoryWhereIs(string id)
{
	Memory *memory = getDownMemory();
	while(memory)
	{
		if(memory->find(id)) return memory;
		memory = memory->parent;
	}
	throw Exception(id + " not exists");
}

void Memory::deleteData(string id) //enlever les références
{
	Memory *memory = getMemoryWhereIs(id);
	Data **slot = findStack(id);
	if(slot)
	{
		TRY_SLOT_DELETE(slot);
		stack.erase(id);
	}
	else
	{
		string ref = getReferenceGlobalUp(id);
		slot = findStack(ref);
		if(slot)
		{
			TRY_SLOT_DELETE(slot);
			stack.erase(ref);
			references.erase(id);
		}
		else
		{
			throw Exception(id + " not exists");
		}
	}
}

void Memory::deletePersistantData(Data **ref)
{
	auto len = persistant.size();
	for(int i = 0; i < len; i++)
	{
		if(persistant[i] == ref)
		{
			delete *ref;
			*ref = nullptr;
			delete ref;
			ref = nullptr;
			persistant.erase(persistant.begin() + i);
			break;
		}
	}
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

Memory *Memory::getUpMemory()
{
	Memory *memory = this;
	while(memory->parent)
	{
		memory = memory->parent;
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
	if(find(id)) return true;
	/*auto accessor = toAccessor(id);
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
	}*/
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
{/*
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
				 		accessor[i] = elem->toString();
				 	}
				 }
			}
			else
			{
				if(Type::type(accessor[i]) == INTEGER_T)
				{
					j = atoi(accessor[i].c_str());
				}
				else
				{
					j = -1;
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
				case TABLE_T:
					if(dynamic_cast<Reference *>(data)) data = dynamic_cast<Reference *>(data)->get();
					data = dynamic_cast<Table *>(data)->get(accessor[i]);
					break;
				default:
					throw Exception(expr + " try to access to a non accessible data type: " + data->type());
			}
		}
		return data;
	}
	throw Exception(expr + " does not represents an accessor expression");*/
return nullptr;
}


Data **Memory::getDataSlotFromAccessor(string expr)
{/*
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
				 		accessor[i] = (*elem)->toString();
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
					j = -1;
				}
			}
			switch((*data)->typeId())
			{
				case VECTOR_T:
					if(dynamic_cast<Reference *>(*data)) data = dynamic_cast<Reference *>(*data)->getSlot();
					if(j < 0 or j >= dynamic_cast<Vector *>(*data)->getVector().size())
						throw Exception(to_string(j) + " is out ouf band of the size of vector");
					data = &dynamic_cast<Vector *>(*data)->getVector()[j];
					break;

				case TABLE_T:
					if(dynamic_cast<Reference *>(*data)) data = dynamic_cast<Reference *>(*data)->getSlot();
					data = dynamic_cast<Table *>(*data)->getAddr(accessor[i]);
					break;
				default:
					throw Exception(expr + " try to access to a non accessible data type: " + (*data)->type());
			}
		}
		return data;
	}
	throw Exception(expr + " does not represents an accessor expression");*/
return nullptr;
}


Data *Memory::getDataGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		Data **slot = nullptr;
		if((slot = memory->find(id)))
		{
			 return *slot;
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

string Memory::getReferenceGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		Data **slot = nullptr;
		if(memory->references.find(id) != memory->references.end())
		{
			 return memory->references[id];
		}
		memory = memory->parent;
	}
	throw Exception(id + " Reference not exists");
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
		for(auto it : memory->stack)
			if(d == *it.second)
				return it.first;
		memory = memory->parent;
	}
	throw Exception("Reference Memory is a reference to a Memory which not exists");
}

Data **Memory::generateDataFromValue(string value)
{
	return Type::generateSlot(Type::generatePrimitive(value));
}

Data **Memory::generateDataFromId(string id)
{
	return Type::generateSlot(getDataGlobalUp(id)->dup());
}

void Memory::addPrimitiveData(string id, string value)
{
	if(not exists(id))
	{
		if(existsGlobalUp(value))
		{
			stack[id] = generateDataFromId(value);
		}
		else
		{
			stack[id] = generateDataFromValue(value);
		}
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

Data **Memory::generateInteger(Data *reference)
{
	return Type::generateSlot(new Integer(reference));
}

Data **Memory::generateInteger(string value)
{
	if(existsGlobalUp(value))
	{
		return generateInteger(getDataGlobalUp(value));
	}
	else
	{
		return Type::generateSlot(new Integer(value));
	}
}


Data **Memory::generateFloat(Data *reference)
{
	return Type::generateSlot(new Float(reference));
}

Data **Memory::generateFloat(string value)
{
	if(existsGlobalUp(value))
	{
		return generateFloat(getDataGlobalUp(value));
	}
	else
	{
		return Type::generateSlot(new Float(value));
	}
}

Data **Memory::generateBool(Data *reference)
{
	return Type::generateSlot(new Bool(reference));
}

Data **Memory::generateBool(string value)
{
	if(existsGlobalUp(value))
	{
		return generateBool(getDataGlobalUp(value));
	}
	else
	{
		return Type::generateSlot(new Bool(value));
	}
}

Data **Memory::generateString(Data *reference)
{
	return Type::generateSlot(new String(reference));
}

Data **Memory::generateString(string value)
{
	if(existsGlobalUp(value))
	{
		return generateString(getDataGlobalUp(value));
	}
	else
	{
		return Type::generateSlot(new String(value));
	}
}

Data **Memory::generateDataSlotPersistant(string value)
{
	Data **slot = generateDataFromValue(value);
	(*slot)->setAttr(PERSISTANT_A);
	persistant.push_back(slot);
	return slot;
}

Data **Memory::generateVector(vector<string>& values)
{
	Vector *data = new Vector();
	for(string value : values)
	{
		if(existsGlobalUp(value))
		{
			data->add(generateDataFromId(value));
		}
		else
		{
			data->add(generateDataFromValue(value));
		}
	}
	return Type::generateSlot(data);
}

Data **Memory::generateTable(string value)
{
	Table *data;
	if(existsGlobalUp(value))
	{
		data = new Table(getDataGlobalUp(value));
	}
	else
	{
		data = new Table();
 	}
	return Type::generateSlot(data);
}

void Memory::addInteger(string id, string value)
{
	if(not exists(id))
	{
		stack[id] = generateInteger(value);
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
		stack[id] = generateFloat(value);
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
		stack[id] = generateBool(value);
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
		stack[id] = generateString(value);
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
		if(existsGlobalUp(value))
		{
			/*if(references.find(value) != references.end())
				value = references[value]; AVOIR N IMPORTE QUELLE REF */ 
			RESTRICT_CONTROL(getDataGlobalUp(value));
			references[id] = value;
		}
		else
		{
			//add persistant memory
		}
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
		stack[id] = generateVector(values);
	}
	else
	{
		throw Exception(id +  " Memory already exists");
	}
}

void Memory::addTable(string id, string value)
{
	if(not exists(id))
	{
		stack[id] = generateTable(value);
	}
	else
	{
		throw Exception(id +  " Memory already exists");
	}
}



Data **Memory::getDataSlotGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		if(memory->exists(id))
		{
			Data **slot = nullptr;
			if((slot = memory->find(id)))
			{
				return slot;
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

void Memory::setDataFromValue(string id, string value)
{
	Data **slot = getDataSlotGlobalUp(id);
	Type::updateSlot(slot, value);
}

void Memory::setDataFromId(string id, string value)
{
	Data **slot = getDataSlotGlobalUp(id);
	Type::updateSlot(slot, getDataGlobalUp(value));
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
	if(exists(id)) return *stack[id];
	throw Exception(id + " Memory does not exists");
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
	if(existsGlobalUp(id))
	{
		if(existsGlobalUp(value))
		{
			RESTRICT_CONTROL(getDataGlobalUp(value));
			references[id] = value;
		}
	}
	else
	{
		throw Exception(id + " not exists");
	}
}


string Memory::getCharAt(string id, string index)
{
	if(existsGlobalUp(id))
	{
		Data **slot = getDataSlotGlobalUp(id);
		if(dynamic_cast<String *>(*slot))
		{
			return ((String *)slot)->getCharAt(index);
		}
		else
		{
			throw Exception(id + " is not a String");
		}
	}
	else
	{
		throw Exception(id + " not exists");
	}
}

void Memory::setCharAt(string id, string index, string character)
{
	if(existsGlobalUp(id))
	{
		Data **slot = getDataSlotGlobalUp(id);
		if(dynamic_cast<String *>(*slot))
		{
			((String *)slot)->setCharAt(index, character);
		}
		else
		{
			throw Exception(id + " is not a String");
		}
	}
	else
	{
		throw Exception(id + " not exists");
	}
}

void Memory::field(string id, string value)
{/*
	if(isAccessor(id))
	{
		auto acc = toAccessor(id);
		int i;
		id = "";
		for(i = 0; i < acc.size() - 1; i++)
		{
			id += acc[i] + ".";
		}
		id.pop_back();
		Data *data = getDataGlobalUp(id);
		if(data->typeId() != TABLE_T) throw Exception(id + " is not a table");
		Table *table = dynamic_cast<Reference *>(data) ? (Table *)dynamic_cast<Reference *>(data)->get() : (Table *)data;

		if(table->getTable().find(acc[i]) == table->getTable().end())
		{
			if(value.size())
			{
				if(existsGlobalUp(value))
				{
					table->set(*generateDataFromId(value), acc[i]);
				}
				else
				{
					table->set(*generateDataFromValue(value), acc[i]);
				}
			}
			else
			{
				table->set(*generateTable(value), acc[i]);
			}
		}
		else
		{
			throw Exception(acc[i] + " field already exists in " + id + " Table");
		}
	}*/
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

string Memory::new_Table(string id, string value)
{
	getDownMemory()->addTable(id, value);
	return id;
}

string Memory::set_memory(string id, string value)
{
	Memory *memory = getDownMemory();
	memory->setData(id, value);
	return id;
}

string Memory::set_reference(string id, string value)
{
	Memory *memory = getDownMemory();
	memory->changeReference(id, value);
	return id;
}

string Memory::field_memory(string id, string value)
{
	Memory *memory = getDownMemory();
	field(id, value);
	return id;
}

int Memory::getDataSize(string id)
{
	Data *data = getDataGlobalUp(id);
	if(dynamic_cast<String *>(data)) return dynamic_cast<String *>(data)->get().size();
	if(dynamic_cast<Vector *>(data)) return dynamic_cast<Vector *>(data)->getVector().size();
	throw Exception("can not take size of a " + data->type());
}

string Memory::get_memory(string id)
{
	return getDownMemory()->toString(id);
}


string Memory::size_memory(string id)
{
	return to_string(getDownMemory()->getDataSize(id));
}


string Memory::get_char_at(string id, string index)
{
	return getDownMemory()->getCharAt(id, index);
}

string Memory::set_char_at(string id, string index, string character)
{
	Memory *memory = getDownMemory();
	memory->setCharAt(id, index, character);
	return id;
}

string Memory::del_data(string id)
{
	deleteData(id);
	return id;
}

string Memory::del_persistant_data(string id)
{
	Data **ref = getDownMemory()->getDataSlotGlobalUp(id);
	if(ref)
		deletePersistantData(ref);
	else
		throw Exception(id + " is not a Reference");
	return id;
}


string Memory::type_memory(string id)
{
	Memory *memory = getDownMemory();
	if(memory->existsGlobalUp(id))
	{
		return memory->getDataGlobalUp(id)->type();
	}
	return Type::inferType(id);
}

string Memory::exists_memory(string id)
{
	return getDownMemory()->existsGlobalUp(id) ? "true" : "false";
}

string Memory::add_attribute(string id, int attr)
{
	Memory *memory = getDownMemory();
	Data **slot = memory->getDataSlotGlobalUp(id);
	memory->addAttr(*slot, attr);
	if(attr == PERSISTANT_A)
	{
		persistant.push_back(slot);
	}
	return id;
}

void Memory::addAttr(Data *data, int attr)
{
	data->setAttr(attr);
}
