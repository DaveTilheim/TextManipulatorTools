#include "MemoryContext.hpp"


using namespace Lizzy;


MemoryContext::MemoryContext(string id, MemoryContext *parent) : id(id), parent(parent), child(nullptr)
{
	cout << "MemoryContext created: " << id <<  endl;
}

MemoryContext::~MemoryContext()
{
	pop();
	cout << "MemoryContext deleted: " << id <<  endl;
}

MemoryContext& MemoryContext::push(string id)
{
	child = new MemoryContext(id, this);
	return *child;
}

void MemoryContext::pop()
{
	if(child)
		delete child;
}

string MemoryContext::getId() const
{
	return id;
}

string MemoryContext::getFullId() const
{
	if(parent) return parent->getFullId() + "." + getId();
	return getId();
}

Memory &MemoryContext::getMemory()
{
	return memory;
}

Memory &MemoryContext::getUpMemory()
{
	return getUpContext().getMemory();
}

Memory &MemoryContext::getDownMemory()
{
	return getDownContext().getMemory();
}

Memory &MemoryContext::getMemoryWhereIs_BeginDown(string id)
{
	MemoryContext *mc = &getDownContext();
	while(mc)
	{
		if(mc->getMemory().exists(id)) return mc->getMemory();
		mc = mc->parent;
	}
	throw Exception(id +  " Memory not exists");
}

Memory &MemoryContext::getMemoryWhereIs_BeginUp(string id)
{
	MemoryContext *mc = &getUpContext();
	while(mc)
	{
		if(mc->getMemory().exists(id)) return mc->getMemory();
		mc = mc->child;
	}
	throw Exception(id +  " Memory not exists");
}

MemoryContext &MemoryContext::getDownContext()
{
	MemoryContext *context = this;
	while(context->child)
	{
		context = context->child;
	}
	return *context;
}

MemoryContext &MemoryContext::getUpContext()
{
	MemoryContext *context = this;
	while(context->parent)
	{
		context = context->parent;
	}
	return *context;
}

MemoryContext &MemoryContext::getChild()
{
	if(child) return *child;
	throw Exception(id +  " MemoryContext has no child");
}

MemoryContext &MemoryContext::getParent()
{
	if(parent) return *parent;
	throw Exception(id +  " MemoryContext has no parent");
}

bool MemoryContext::exists(string id)
{
	MemoryContext *mc = this;
	while(mc)
	{
		if(mc->getMemory().exists(id)) return true;
		mc = mc->child;
	}
	return false;
}

string MemoryContext::new_primitive(string id, string value)
{
	MemoryContext& context = getDownContext();
	return context.getDownMemory().new_primitive(id, value);
}

string MemoryContext::new_Integer(string id, string value)
{
	MemoryContext& context = getDownContext();
	return context.getDownMemory().new_Integer(id, value);
}

string MemoryContext::new_Float(string id, string value)
{
	MemoryContext& context = getDownContext();
	return context.getDownMemory().new_Float(id, value);
}

string MemoryContext::new_Bool(string id, string value)
{
	MemoryContext& context = getDownContext();
	return context.getDownMemory().new_Bool(id, value);
}

string MemoryContext::new_String(string id, string value)
{
	MemoryContext& context = getDownContext();
	return context.getDownMemory().new_String(id, value);
}

string MemoryContext::set_memory(string id, string value)
{
	return getMemoryWhereIs_BeginDown(id).set_memory(id, value);
}

string MemoryContext::get_memory(string id)
{
	return getMemoryWhereIs_BeginDown(id).get_memory(id);
}

string MemoryContext::type_memory(string idvalue)
{
	try
	{
		return getMemoryWhereIs_BeginDown(idvalue).data_type_memory(idvalue);
	}
	catch(...)
	{
		return Memory::value_type_memory(idvalue);
	}
}

string MemoryContext::exists_memory(string id)
{
	return exists(id) ? "true" : "false";
}
