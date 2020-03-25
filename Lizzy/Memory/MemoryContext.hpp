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
		string getId() const;
		string getFullId() const;
		Memory &getMemory();
		Memory &getDownMemory(); //get last child memoryMap
		Memory &getUpMemory(); //get first child memoryMap
		Memory &getMemoryWhereIs_BeginDown(string id); //get last child memoryMap that contains id Memory
		Memory &getMemoryWhereIs_BeginUp(string id); //get last child memoryMap that contains id Memory
		MemoryContext &getDownContext(); //get last child
		MemoryContext &getUpContext(); //get last child
		MemoryContext &getChild();
		MemoryContext &getParent();
		bool exists(string id);
	public: //Command traitement layer
		string new_primitive(string id, string value);
		string new_Integer(string id, string value);
		string new_Float(string id, string value);
		string new_Bool(string id, string value);
		string new_String(string id, string value);
		string new_primitive(string id, string value, const DataAttributes& attr);
		string new_Integer(string id, string value, const DataAttributes& attr);
		string new_Float(string id, string value, const DataAttributes& attr);
		string new_Bool(string id, string value, const DataAttributes& attr);
		string new_String(string id, string value, const DataAttributes& attr);
		string set_memory(string id, string value);
		string get_memory(string id);
		string type_memory(string id);
		string exists_memory(string id);

	};
}


#endif
