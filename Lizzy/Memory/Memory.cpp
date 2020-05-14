#include "Memory.hpp"

using namespace Lizzy;

PersistantMemory Memory::persistant = PersistantMemory();


Memory::Memory(Memory *parent, string id) : parent(parent), id(id), stack()
{
	cout << "Memory created" << endl;
}

Memory::~Memory()
{
	for(auto it : stack)
	{
		cout << it.first << endl;
		deleteData(it.first);
	}
	stack.clear();
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
			cout << endl << "[ " << it.first << " ]" << endl;
			cout << it.second->toString() << endl;
		}
		memory = memory->child;
		i++;
	}
}

void Memory::trace(string id)
{
	if(existsGlobalUp(id))
	{
		Slot *slot = getDataSlotGlobalUp(id);
		cout << endl << "[ " << id << " ]" << endl;
		cout << slot->toString() << endl;
	}
	else
	{
		throw Exception(id + " not exists");
	}
}


Slot *Memory::getPersistantDataSlot(Data *data)
{
	auto len = persistant.size();
	for(int i = 0; i < len ; i++)
	{
		if(data == *persistant[i]->get()) return persistant[i];
	}
	throw Exception("Data is not persistant");
	return nullptr;
}

void Memory::erasePersistantMemory()
{
	for(Slot *slot : persistant)
	{
		delete *slot->get();
		delete slot->get();
		delete slot;
	}
}

Slot* Memory::find(string id)
{
	return stack.find(id) == stack.end() ? nullptr : stack[id];
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

void Memory::deleteData(string id)
{
	Memory *memory = getMemoryWhereIs(id);
	Slot *slot = find(id);
	if(slot)
	{
		delete slot;
		stack.erase(id);
	}
	else
	{
		throw Exception(id + " not exists");
	}
}

void Memory::deletePersistantData(Slot *ref)
{
	auto len = persistant.size();
	for(int i = 0; i < len; i++)
	{
		if(persistant[i]->get() == ref->get())
		{
			delete *ref->get();
			delete ref->get();
			delete persistant[i];
			persistant.erase(persistant.begin() + i);
			ref->referenceTo(nullptr);
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

bool Memory::isAccessor(Data *data)
{
	return data->typeId() == VECTOR_T or data->typeId() == TABLE_T or data->typeId() == OBJECT_T;
}

bool Memory::existsAsAccessor(string expr)
{
	auto accessor = toAccessor(expr);
	if(accessor.size() > 1)
	{
		Slot *slot = find(accessor[0]);
		if(slot)
		{
			if(isAccessor(*slot->get()))
			{
				return true;
			}
		}
	}
	return false;
}

bool Memory::exists(string id)
{
	if(find(id)) return true;
	return existsAsAccessor(id);
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

Slot *Memory::getSlotFromVectorAccessor(Slot *slot, string indexExpr)
{
	cmd::String expr = indexExpr;
	long index = -1;
	if(expr.isPacked("{"))
	{
		expr.unpack("{");
		Slot *tmp = getDataSlotGlobalUp((string)expr);
		index = Type::extractIndex(tmp);
	}
	else
	{
		index = Type::extractIndex(expr);
	}
	return dynamic_cast<Vector *>(*slot->get())->get(index);
}

Slot *Memory::getSlotFromFieldAccessor(Slot *slot, string fieldExpr)
{
	cmd::String expr = fieldExpr;
	string field;
	if(expr.isPacked("{"))
	{
		expr.unpack("{");
		Slot *tmp = getDataSlotGlobalUp((string)expr);
		field = (*tmp->get())->toString();
	}
	else
	{
		field = expr;
	}
	return dynamic_cast<Table *>(*slot->get())->get(field);
}

Slot *Memory::getDataSlotFromAccessor(string expr)
{
	auto accessor = toAccessor(expr);
	auto len = accessor.size();
	Slot *slot = getDataSlotGlobalUp(accessor[0]);
	for(int i = 1; i < len; i++)
	{
		if(dynamic_cast<Vector *>(*slot->get()))
		{
			slot = getSlotFromVectorAccessor(slot, accessor[i]);
		}
		else
		{
			slot = getSlotFromFieldAccessor(slot, accessor[i]);
		}
	}
	return slot;
}


Data *Memory::getDataFromAccessor(string expr)
{
	return *getDataSlotFromAccessor(expr)->get();
}


Data *Memory::getDataGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		Slot *slot = nullptr;
		if((slot = memory->find(id)))
		{
			 return *slot->get();
		}
		else
		{
			if(existsAsAccessor(id))
			{
				return getDataFromAccessor(id);
			}
		}
		memory = memory->parent;
	}
	throw Exception(id + " Memory not exists");
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
			if(d == *it.second->get())
				return it.first;
		memory = memory->parent;
	}
	throw Exception("Reference Memory is a reference to a Memory which not exists");
}

Slot *Memory::generateDataFromValue(string value)
{
	return new Slot(Type::generateSlot(Type::generatePrimitive(value)));
}

Slot *Memory::generateDataFromId(string id)
{
	return new Slot(Type::generateSlot(getDataGlobalUp(id)->dup()));
}

Slot *Memory::generateDataSlot(string value)
{
	return existsGlobalUp(value) ? generateDataFromId(value) : generateDataFromValue(value);
}

void Memory::addPrimitiveData(string id, string value)
{
	if(not exists(id))
	{
		stack[id] = generateDataSlot(value);
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

Slot *Memory::generateInteger(Data *reference)
{
	return new Slot(Type::generateSlot(new Integer(reference)));
}

Slot *Memory::generateInteger(string value)
{
	if(existsGlobalUp(value))
	{
		return generateInteger(getDataGlobalUp(value));
	}
	else
	{
		return new Slot(Type::generateSlot(new Integer(value)));
	}
}


Slot *Memory::generateFloat(Data *reference)
{
	return new Slot(Type::generateSlot(new Float(reference)));
}

Slot *Memory::generateFloat(string value)
{
	if(existsGlobalUp(value))
	{
		return generateFloat(getDataGlobalUp(value));
	}
	else
	{
		return new Slot(Type::generateSlot(new Float(value)));
	}
}

Slot *Memory::generateBool(Data *reference)
{
	return new Slot(Type::generateSlot(new Bool(reference)));
}

Slot *Memory::generateBool(string value)
{
	if(existsGlobalUp(value))
	{
		return generateBool(getDataGlobalUp(value));
	}
	else
	{
		return new Slot(Type::generateSlot(new Bool(value)));
	}
}

Slot *Memory::generateString(Data *reference)
{
	return new Slot(Type::generateSlot(new String(reference)));
}

Slot *Memory::generateString(string value)
{
	if(existsGlobalUp(value))
	{
		return generateString(getDataGlobalUp(value));
	}
	else
	{
		return new Slot(Type::generateSlot(new String(value)));
	}
}

Slot *Memory::generateDataSlotPersistant(string value)
{
	Slot *slot = generateDataFromValue(value);
	slot->attribs = PERSISTANT_A;
	persistant.push_back(slot);
	return slot;
}

Slot *Memory::generateVector(vector<string>& values)
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
	return new Slot(Type::generateSlot(data));
}

Slot *Memory::generateTable(string value)
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
	return new Slot(Type::generateSlot(data));
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

Slot *Memory::generateReference(string value)
{
	if(value.size())
	{
		if(existsGlobalUp(value))
		{
			Slot *slot = getDataSlotGlobalUp(value);
			if(slot->isRestrict()) throw Exception(value + " is marked restrict, it can not be referenced");
			return new Slot(slot);
		}
		else
		{
			Slot *slot = generateDataSlotPersistant(value);
			return new Slot(slot);
		}
	}
	else
	{
		return new Slot((Slot *)nullptr);
	}
}

void Memory::addReference(string id, string value)
{
	if(not exists(id))
	{
		stack[id] = generateReference(value);
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::addReference(string id)
{
	if(not exists(id))
	{
		stack[id] = generateReference("");
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



Slot *Memory::getDataSlotGlobalUp(string id)
{
	Memory *memory = this;
	while(memory)
	{
		if(memory->exists(id))
		{
			Slot *slot = nullptr;
			if((slot = memory->find(id)))
			{
				return slot;
			}
			else if(memory->existsAsAccessor(id))
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
	Slot *slot = getDataSlotGlobalUp(id);
	Type::updateSlot(slot, value);
}

void Memory::setDataFromId(string id, string value)
{
	Slot *slot = getDataSlotGlobalUp(id);
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
	if(exists(id)) return *stack[id]->get();
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
			Slot *refSlot = getDataSlotGlobalUp(id);
			Slot *targetSlot = getDataSlotGlobalUp(value);
			refSlot->referenceTo(targetSlot);
		}
		else
		{
			Slot *refSlot = getDataSlotGlobalUp(id);
			Slot *targetSlot = generateDataSlotPersistant(value);
			refSlot->referenceTo(targetSlot);
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
		Slot*slot = getDataSlotGlobalUp(id);
		if(dynamic_cast<String *>(*slot->get()))
		{
			return ((String *)*slot->get())->getCharAt(index);
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
		Slot *slot = getDataSlotGlobalUp(id);
		if(dynamic_cast<String *>(*slot->get()))
		{
			dynamic_cast<String *>(*slot->get())->setCharAt(index, character);
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
	value.size() ? getDownMemory()->addReference(id, value) : getDownMemory()->addReference(id);
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
	Slot *ref = getDownMemory()->getDataSlotGlobalUp(id);
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


string Memory::add_slot_attribute(string id, int attr)
{
	Memory *memory = getDownMemory();
	Slot *slot = memory->getDataSlotGlobalUp(id);
	memory->addSlotAttr(slot, attr);
	return id;
}

void Memory::addSlotAttr(Slot *data, int attr)
{
	data->attribs |= attr;
	if(attr == PERSISTANT_A)
	{
		persistant.push_back(new Slot(data));
	}
}





void Memory::field(string id, string field, Slot*(Memory::*generator)(string), string value)
{
	if(existsGlobalUp(id))
	{
		Slot *slot = getDataSlotGlobalUp(id);
		if(dynamic_cast<Table *>(*slot->get()))
		{
			cmd::String expr = field;
			if(expr.isPacked("{"))
			{
				expr.unpack("{");
				if(existsGlobalUp((string)expr))
				{
					Slot *value = getDataSlotGlobalUp((string)expr);
					expr = (*value->get())->toString();
				}
				else
				{
					Exception(expr + " not exists");
				}
			}
			Type::setField(slot, expr, invoke(generator, *this, value));
		}
		else
		{
			throw Exception(id + " is not a Table");
		}
	}
	else
	{
		throw Exception(id + " not exists");
	}
}

string Memory::field_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateDataSlot, value);
	return id + "." + fieldn;
}

string Memory::field_Integer_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateInteger, value);
	return id + "." + fieldn;
}

string Memory::field_Float_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateFloat, value);
	return id + "." + fieldn;
}

string Memory::field_Bool_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateBool, value);
	return id + "." + fieldn;
}

string Memory::field_String_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateString, value);
	return id + "." + fieldn;
}

string Memory::field_Reference_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateReference, value);
	return id + "." + fieldn;
}

string Memory::field_Vector_memory(string id, string fieldn, string value)
{
	//getDownMemory()->field(id, fieldn, &Memory::generateVector, value);
	return id + "." + fieldn;
}

string Memory::field_Table_memory(string id, string fieldn, string value)
{
	getDownMemory()->field(id, fieldn, &Memory::generateTable, value);
	return id + "." + fieldn;
}
