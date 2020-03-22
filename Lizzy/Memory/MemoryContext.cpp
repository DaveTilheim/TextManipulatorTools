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

string MemoryContext::getFullId() const
{
	if(parent) return parent->getFullId() + "." + id;
	return id;
}

Memory &MemoryContext::getMemory()
{
	if(child) return child->getMemory();
	return memory;
}

Memory &MemoryContext::getMemory(string id)
{
	MemoryContext *mc = &getContext();
	while(mc)
	{
		if(mc->getMemory().exists(id)) return mc->getMemory();
		mc = mc->parent;
	}
	throw Exception(id +  " Memory not exists");
}

MemoryContext &MemoryContext::getContext()
{
	if(child) return child->getContext();
	return *this;
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


string MemoryContext::new_primitive(string id, string value)
{
	MemoryContext& context = getContext();
	return context.getMemory().new_primitive(id, value);
}
