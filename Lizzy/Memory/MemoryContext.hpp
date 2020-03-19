#ifndef MEMORY_CONTEXT_HPP
#define MEMORY_CONTEXT_HPP
#include "Memory.hpp"


class MemoryContext
{
private:
	const string id;
	Memory memory;
	MemoryContext *parent;
	MemoryContext *child;
public:
	MemoryContext(string id, MemoryContext *parent=nullptr);
	~MemoryContext();
	MemoryContext& push(string id);
	void pop();
	string getFullId() const;
	Memory &getMemory(); //get last child memoryMap
	Memory &getMemory(string id); //get last child memoryMap that contains id Memory
	MemoryContext &getMemoryContext(); //get last child
	MemoryContext &getChild();
	MemoryContext &getParent();
};


#endif
