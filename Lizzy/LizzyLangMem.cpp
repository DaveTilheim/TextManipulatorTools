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

_def_action(MemPkg::new_Integer_action)
{
	string id = args("id");
	string value = args("value", 1); 
	return MemPkg::memoryContext.new_Integer(id, value);
}

_def_action(MemPkg::new_Float_action)
{
	string id = args("id");
	string value = args("value", 1); 
	return MemPkg::memoryContext.new_Float(id, value);
}

_def_action(MemPkg::new_Bool_action)
{
	string id = args("id");
	string value = args("value", 1); 
	return MemPkg::memoryContext.new_Bool(id, value);
}

_def_action(MemPkg::new_String_action)
{
	string id = args("id");
	string value = args("value", 1); 
	return MemPkg::memoryContext.new_String(id, value);
}



_def_action(MemPkg::new_const_action)
{
	string id = args("id");
	string value = args("value", 1);
	DataAttributes attr;
	attr._const = true;
	return MemPkg::memoryContext.new_primitive(id, value, attr);
}

_def_action(MemPkg::new_const_Integer_action)
{
	string id = args("id");
	string value = args("value", 1); 
	DataAttributes attr;
	attr._const = true;
	return MemPkg::memoryContext.new_Integer(id, value, attr);
}

_def_action(MemPkg::new_const_Float_action)
{
	string id = args("id");
	string value = args("value", 1); 
	DataAttributes attr;
	attr._const = true;
	return MemPkg::memoryContext.new_Float(id, value, attr);
}

_def_action(MemPkg::new_const_Bool_action)
{
	string id = args("id");
	string value = args("value", 1);
	DataAttributes attr;
	attr._const = true; 
	return MemPkg::memoryContext.new_Bool(id, value, attr);
}

_def_action(MemPkg::new_const_String_action)
{
	string id = args("id");
	string value = args("value", 1);
	DataAttributes attr;
	attr._const = true;
	return MemPkg::memoryContext.new_String(id, value, attr);
}








_def_action(MemPkg::set_action)
{
	string id = args("id");
	string value = args("value", 1);
	return MemPkg::memoryContext.set_memory(id, value);
}

_def_action(MemPkg::get_action)
{
	string id = args("id");
	return MemPkg::memoryContext.get_memory(id);
}

_def_action(MemPkg::type_action)
{
	string value = args.list();
	return MemPkg::memoryContext.type_memory(value);
}

_def_action(MemPkg::exists_action)
{
	string value = args("id");
	return MemPkg::memoryContext.exists_memory(value);
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
	newAction.setNamed("id");
	newAction.setNamed("value");
	cmd("new").setAction(2, newAction);
	Action newIntegerAction(new_Integer_action);
	newIntegerAction.setNamed("id");
	newIntegerAction.setNamed("value");
	Action newFloatAction(new_Float_action);
	newFloatAction.setNamed("id");
	newFloatAction.setNamed("value");
	Action newBoolAction(new_Bool_action);
	newBoolAction.setNamed("id");
	newBoolAction.setNamed("value");
	Action newStringAction(new_String_action);
	newStringAction.setNamed("id");
	newStringAction.setNamed("value");
	cmd("new").child("Integer").setAction(2, newIntegerAction);
	cmd("new").child("Float").setAction(2, newFloatAction);
	cmd("new").child("Bool").setAction(2, newBoolAction);
	cmd("new").child("String").setAction(2, newStringAction);

	Action newConstAction(new_const_action);
	newConstAction.setNamed("id");
	newConstAction.setNamed("value");
	cmd("new").child("const").setAction(2, newConstAction);

	Action newConstIntegerAction(new_const_Integer_action);
	newConstIntegerAction.setNamed("id");
	newConstIntegerAction.setNamed("value");
	Action newConstFloatAction(new_const_Float_action);
	newConstFloatAction.setNamed("id");
	newConstFloatAction.setNamed("value");
	Action newConstBoolAction(new_const_Bool_action);
	newConstBoolAction.setNamed("id");
	newConstBoolAction.setNamed("value");
	Action newConstStringAction(new_const_String_action);
	newConstStringAction.setNamed("id");
	newConstStringAction.setNamed("value");
	cmd("new").child("const").child("Integer").setAction(2, newConstIntegerAction);
	cmd("new").child("const").child("Float").setAction(2, newConstFloatAction);
	cmd("new").child("const").child("Bool").setAction(2, newConstBoolAction);
	cmd("new").child("const").child("String").setAction(2, newConstStringAction);

	cmd("var").setAction(2, newAction);
	cmdAlias(cmd("new").child("const"), "const");
	cmdAlias(cmd("new").child("Integer"), "Integer");
	cmdAlias(cmd("new").child("Float"), "Float");
	cmdAlias(cmd("new").child("Bool"), "Bool");
	cmdAlias(cmd("new").child("String"), "String");
	


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
	Action existsAction(exists_action);
	{
		existsAction.setNamed("id");
		cmd("exists").setAction(1, existsAction);
	}
}
