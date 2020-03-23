#ifndef MEMORY_CONTEXT_HPP
#define MEMORY_CONTEXT_HPP
#include "Memory.hpp"

namespace Lizzy
{
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
		MemoryContext &getContext(); //get last child
		MemoryContext &getChild();
		MemoryContext &getParent();
		bool exists(string id);
	public: //Command traitement layer
		string new_primitive(string id, string value);
		string set_memory(string id, string value);
		string get_memory(string id);
		string type_memory(string id);
		string exists_memory(string id);
	};
}


#endif
