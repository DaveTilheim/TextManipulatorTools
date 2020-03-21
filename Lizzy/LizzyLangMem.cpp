#include "LizzyLangMem.hpp"

using namespace Lizzy;


MemoryContext *MemPkg::_memoryContext = new MemoryContext("root");
MemoryContext& MemPkg::memoryContext = *MemPkg::_memoryContext;

_def_action(MemPkg::new_action)
{
	string id = args("id");
	string value = args("value", 1); 
	//cout << value << endl;
	MemPkg::memoryContext.getMemory().addMemory(id, value);
	return id;
}

_def_action(MemPkg::news_action)
{
	string id = args("id");
	string value = Memory::VECTOR_ID;
	args.list().next();
	while(not args.list().oob())
	{
		value += (string)args.list() + Memory::VECTOR_ELEM_SEP_ID;
	}
	if(value.size()) value.pop_back();
	args.namedArgList["value"] = value;
	return new_action(args);
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

_def_action(MemPkg::get_2_action)
{
	string id = args("id");
	int index = Tokens(args("index", 1));
	return MemPkg::memoryContext.getMemory(id).getVectorElement(id, index);
}

_def_action(MemPkg::gets_action)
{
	string id = args("id");
	return MemPkg::memoryContext.getMemory(id).toString(id, true);
}

_def_action(MemPkg::type_action)
{
	string id = args("id");
	if(id == "unused") id = args("value");
	try
	{
		return MemPkg::memoryContext.getMemory(id).getType(id);
	}
	catch(...)
	{
		return MemPkg::memoryContext.getMemory().constType(id);
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
	Action newsAction(news_action);
	{
		newsAction.setNamed("id");
		cmd("news").setAction(-1, newsAction);
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
	Action get2Action(get_2_action);
	{
		get2Action.setNamed("id");
		get2Action.setNamed("index");
		cmd("get").setAction(2, get2Action);
	}
	Action getsAction(gets_action);
	{
		getsAction.setNamed("id");
		cmd("gets").setAction(1, getsAction);
	}
	Action typeAction(type_action);
	{
		typeAction.setNamed("id");
		typeAction.setNamed("value");
		cmd("type").setAction(1, typeAction);
	}
}
