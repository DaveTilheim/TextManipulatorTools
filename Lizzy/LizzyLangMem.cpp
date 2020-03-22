#include "LizzyLangMem.hpp"

using namespace Lizzy;


MemoryContext *MemPkg::_memoryContext = new MemoryContext("root");
MemoryContext& MemPkg::memoryContext = *MemPkg::_memoryContext;

_def_action(MemPkg::new_action)
{
	string id = args("id");
	string value = args("value", 1); 
	return MemPkg::memoryContext.new_primitive(id, value);
}


_def_action(MemPkg::set_action)
{
	string id = args("id");
	string value = args("value", 1);
	//MemPkg::memoryContext.getMemory(id).setMemory(id, value);
	return id;
}

_def_action(MemPkg::get_action)
{
	string id = args("id");
	return MemPkg::memoryContext.getMemory(id).toString(id);
}

_def_action(MemPkg::type_action)
{
	string value = args.list();
	try
	{
		return MemPkg::memoryContext.getMemory(value).getType(value);
	}
	catch(...)
	{
		return Memory::inferType(value);
	}
}




MemPkg::MemPkg() : Package("Mem")
{
	CALL_ONCE
}

MemPkg::~MemPkg()
{
	delete MemPkg::_memoryContext;
}

void MemPkg::load()
{
	CALL_ONCE
	Action newAction(new_action);
	{
		newAction.setNamed("id");
		newAction.setNamed("value");
		cmd("new").setAction(2, newAction);
	}
	Action setAction(set_action);
	{
		setAction.setNamed("id");
		setAction.setNamed("value");
		cmd("set").setAction(2, setAction);
	}
	Action getAction(get_action);
	{
		getAction.setNamed("id");
		cmd("get").setAction(1, getAction);
	}
	Action typeAction(type_action);
	{
		cmd("type").setAction(1, typeAction);
	}
}
