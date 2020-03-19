#include "LizzyLangMem.hpp"

using namespace Lizzy;


MemoryContext MemPkg::memoryContext = MemoryContext("root");

_def_action(MemPkg::new_action)
{
	string id = args("id");
	string value = args("value", 1); 
	MemPkg::memoryContext.getMemory().addMemory(id, value);
	return id;
}


_def_action(MemPkg::set_action)
{
	string id = args("id");
	string value = args("value", 1);
	MemPkg::memoryContext.getMemory(id).setMemory(id, value);
	return id;
}

_def_action(MemPkg::get_action)
{
	string id = args("id");
	return MemPkg::memoryContext.getMemory(id).toString(id);
}

_def_action(MemPkg::type_action)
{
	string id = args("id");
	return MemPkg::memoryContext.getMemory(id).getType(id);
}

_def_action(MemPkg::add_action)
{
	string id = args("id");
	return "null";
}



MemPkg::MemPkg() : Package("Mem")
{
	
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
		typeAction.setNamed("id");
		cmd("type").setAction(1, typeAction);
	}
}
