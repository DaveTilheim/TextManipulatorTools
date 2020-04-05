#include "LizzyLangMem.hpp"

using namespace Lizzy;


Memory *MemPkg::_memoryContext = new Memory(nullptr, "root");
Memory& MemPkg::memoryContext = *MemPkg::_memoryContext;

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

_def_action(MemPkg::new_Reference_action)
{
	string id = args("id");
	string value = args("value", 1); 
	return MemPkg::memoryContext.new_Reference(id, value);
}


_def_action(MemPkg::new_Integer_action_1)
{
	string id = args("id");
	return MemPkg::memoryContext.new_Integer(id, "0");
}

_def_action(MemPkg::new_Float_action_1)
{
	string id = args("id");
	return MemPkg::memoryContext.new_Float(id, "0.0");
}

_def_action(MemPkg::new_Bool_action_1)
{
	string id = args("id");
	return MemPkg::memoryContext.new_Bool(id, "false");
}

_def_action(MemPkg::new_String_action_1)
{
	string id = args("id");
	return MemPkg::memoryContext.new_String(id, "");
}

_def_action(MemPkg::new_Reference_action_1)
{
	string id = args("id");
	return MemPkg::memoryContext.new_Reference(id, "");
}




_def_action(MemPkg::const_action)
{
	string id = args("id");
	return MemPkg::memoryContext.add_attribute(id, CONST_A);
}

_def_action(MemPkg::final_action)
{
	string id = args("id");
	return MemPkg::memoryContext.add_attribute(id, FINAL_A);
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

_def_action(MemPkg::set_reference_action)
{
	string id = args("id");
	string value = args("value", 1);
	return MemPkg::memoryContext.set_reference(id, value);
}

/* CONTAINERS */

_def_action(MemPkg::new_Vector_action)
{
	if(args.list().size() == 0) throw Exception("new Vector Command must have at least one parameter");
	string id = args("id");
	vector<string> values;
	args.list().next();
	while(not args.list().oob())
	{
		values.push_back((string)args.list());
	}
	return MemPkg::memoryContext.new_Vector(id, values);
}

_def_action(MemPkg::set_at_action)
{
	string id = args("id");
	string index = args("i", 1);
	string value = args("value", 2);
	return MemPkg::memoryContext.set_at(id, index, value);
}

/* BRANCHS */

_def_action(MemPkg::push_action)
{
	string id = args("id");
	MemPkg::memoryContext.push(id);
	return id;
}

_def_action(MemPkg::pop_action)
{
	MemPkg::memoryContext.pop();
	return "null";
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
	Action newReferenceAction(new_Reference_action);
	newReferenceAction.setNamed("id");
	newReferenceAction.setNamed("value");
	Action newIntegerAction1(new_Integer_action_1);
	newIntegerAction1.setNamed("id");
	Action newFloatAction1(new_Float_action_1);
	newFloatAction1.setNamed("id");
	Action newBoolAction1(new_Bool_action_1);
	newBoolAction1.setNamed("id");
	Action newStringAction1(new_String_action_1);
	newStringAction1.setNamed("id");
	Action newReferenceAction1(new_Reference_action_1);
	newReferenceAction1.setNamed("id");
	cmd("new").child("Integer").setAction(2, newIntegerAction);
	cmd("new").child("Integer").setAction(1, newIntegerAction1);
	cmd("new").child("Float").setAction(2, newFloatAction);
	cmd("new").child("Float").setAction(1, newFloatAction1);
	cmd("new").child("Bool").setAction(2, newBoolAction);
	cmd("new").child("Bool").setAction(1, newBoolAction1);
	cmd("new").child("String").setAction(2, newStringAction);
	cmd("new").child("String").setAction(1, newStringAction1);
	cmd("new").child("Reference").setAction(2, newReferenceAction);
	cmd("new").child("Reference").setAction(1, newReferenceAction1);

	Action newVectorAction(new_Vector_action);
	newVectorAction.setNamed("id");
	cmd("new").child("Vector").setAction(-1, newVectorAction);

	Action setAtAction(set_at_action);
	setAtAction.setNamed("id");
	setAtAction.setNamed("i");
	setAtAction.setNamed("value");
	cmd("set").child("at").setAction(3, setAtAction);



	cmd("var").setAction(2, newAction);
	cmdAlias(cmd("new").child("Integer"), "Integer");
	cmdAlias(cmd("new").child("Float"), "Float");
	cmdAlias(cmd("new").child("Bool"), "Bool");
	cmdAlias(cmd("new").child("String"), "String");
	cmdAlias(cmd("new").child("Reference"), "Reference");
	cmdAlias(cmd("new").child("Vector"), "Vector");

	Action constAction(const_action);
	constAction.setNamed("id");
	cmd("const").setAction(1, constAction);

	Action finalAction(final_action);
	finalAction.setNamed("id");
	cmd("final").setAction(1, finalAction);
	


	Action setAction(set_action);
		setAction.setNamed("id");
		setAction.setNamed("value");
		cmd("set").setAction(2, setAction);

	Action setReferenceAction(set_reference_action);
		setReferenceAction.setNamed("id");
		setReferenceAction.setNamed("value");
		cmd("set").child("reference").setAction(2, setReferenceAction);
	
	Action getAction(get_action);
		getAction.setNamed("id");
		cmd("get").setAction(1, getAction);

	Action typeAction(type_action);
		cmd("type").setAction(1, typeAction);

	Action existsAction(exists_action);
		existsAction.setNamed("id");
		cmd("exists").setAction(1, existsAction);


	Action pushAction(push_action);
		pushAction.setNamed("id");
		cmd("push").setAction(1, pushAction);

	Action popAction(pop_action);
		cmd("pop").setAction(0, popAction);
}
