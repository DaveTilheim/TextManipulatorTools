#include "LizzyLangMemOpe.hpp"



using namespace Lizzy;


Memory *OpePkg::memoryContext = nullptr;


_def_action(OpePkg::add_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->add_memory(n1, n2);
}


_def_action(OpePkg::sub_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->sub_memory(n1, n2);
}

_def_action(OpePkg::mul_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->mul_memory(n1, n2);
}


_def_action(OpePkg::div_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->div_memory(n1, n2);
}

_def_action(OpePkg::mod_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->mod_memory(n1, n2);
}


_def_action(OpePkg::land_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->land_memory(n1, n2);
}

_def_action(OpePkg::lor_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->lor_memory(n1, n2);
}


_def_action(OpePkg::lxor_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->lxor_memory(n1, n2);
}

_def_action(OpePkg::lnot_action)
{
	string n1 = args.list();
	return memoryContext->lnot_memory(n1);
}

_def_action(OpePkg::pre_inc_action)
{
	string n1 = args.list();
	return memoryContext->pre_inc_memory(n1);
}

_def_action(OpePkg::post_inc_action)
{
	string n1 = args.list();
	return memoryContext->post_inc_memory(n1);
}

_def_action(OpePkg::pre_dec_action)
{
	string n1 = args.list();
	return memoryContext->pre_dec_memory(n1);
}

_def_action(OpePkg::post_dec_action)
{
	string n1 = args.list();
	return memoryContext->post_dec_memory(n1);
}


_def_action(OpePkg::and_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->and_memory(n1, n2);
}

_def_action(OpePkg::or_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->or_memory(n1, n2);
}

_def_action(OpePkg::not_action)
{
	string n1 = args.list();
	return memoryContext->not_memory(n1);
}


_def_action(OpePkg::rshift_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->rshift_memory(n1, n2);
}

_def_action(OpePkg::lshift_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->lshift_memory(n1, n2);
}

_def_action(OpePkg::ternary_action)
{
	string n1 = args.list();
	string n2 = args.list();
	string n3 = args.list();
	return memoryContext->ternary_memory(n1, n2, n3);
}

_def_action(OpePkg::equal_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->equal_memory(n1, n2);
}

_def_action(OpePkg::not_equal_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->not_equal_memory(n1, n2);
}
_def_action(OpePkg::lesser_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->lesser_memory(n1, n2);
}
_def_action(OpePkg::bigger_action)
{
	string n1 = args.list();
	string n2 = args.list();
	return memoryContext->bigger_memory(n1, n2);
}


_def_action(OpePkg::as_Integer_action)
{
	string n1 = args("*value");
	return memoryContext->as_Integer(n1);
}

_def_action(OpePkg::as_Float_action)
{
	string n1 = args("*value");
	return memoryContext->as_Float(n1);
}

_def_action(OpePkg::as_Bool_action)
{
	string n1 = args("*value");
	return memoryContext->as_Bool(n1);
}

_def_action(OpePkg::as_String_action)
{
	string n1 = args("*value");
	return memoryContext->as_String(n1);
}


OpePkg::OpePkg(Memory *mc) : Package("Ope")
{
	memoryContext = mc;
}

void OpePkg::load()
{
	CALL_ONCE

	Action addAction(add_action);
	cmd("add").setAction(2, addAction);
	Action subAction(sub_action);
	cmd("sub").setAction(2, subAction);
	Action mulAction(mul_action);
	cmd("mul").setAction(2, mulAction);
	Action divAction(div_action);
	cmd("div").setAction(2, divAction);
	Action modAction(mod_action);
	cmd("mod").setAction(2, modAction);

	Action landAction(land_action);
	cmd("land").setAction(2, landAction);
	Action lorAction(lor_action);
	cmd("lor").setAction(2, lorAction);
	Action lxorAction(lxor_action);
	cmd("lxor").setAction(2, lxorAction);
	Action lnotAction(lnot_action);
	cmd("lnot").setAction(1, lnotAction);

	Action preIncAction(pre_inc_action);
	cmd("pre").child("inc").setAction(1, preIncAction);
	Action postIncAction(post_inc_action);
	cmd("post").child("inc").setAction(1, postIncAction);
	Action preDecAction(pre_dec_action);
	cmd("pre").child("dec").setAction(1, preDecAction);
	Action postDecAction(post_dec_action);
	cmd("post").child("dec").setAction(1, postDecAction);

	cmdAlias(cmd("pre").child("inc"), "inc");
	cmdAlias(cmd("pre").child("dec"), "dec");

	Action andAction(and_action);
	cmd("and").setAction(2, andAction);
	Action orAction(or_action);
	cmd("or").setAction(2, orAction);
	Action notAction(not_action);
	cmd("not").setAction(1, notAction);

	Action rshiftAction(rshift_action);
	cmd("rshift").setAction(2, rshiftAction);
	Action lshiftAction(lshift_action);
	cmd("lshift").setAction(2, lshiftAction);

	cmdAlias(cmd("rshift"), "shr");
	cmdAlias(cmd("lshift"), "shl");

	Action ternaryAction(ternary_action);
	cmd("ternary").setAction(3, ternaryAction);


	Action equalAction(equal_action);
	cmd("equal").setAction(2, equalAction);

	Action notEqualAction(not_equal_action);
	cmd("not").child("equal").setAction(2, notEqualAction);

	Action lesserAction(lesser_action);
	cmd("lesser").setAction(2, lesserAction);

	Action biggerAction(bigger_action);
	cmd("bigger").setAction(2, biggerAction);
	

	
	Action asIntegerAction(as_Integer_action);
	asIntegerAction.setNamed("*value");
	cmd("as").child("Integer").setAction(1, asIntegerAction);
	Action asFloatAction(as_Float_action);
	asFloatAction.setNamed("*value");
	cmd("as").child("Float").setAction(1, asFloatAction);
	Action asBoolAction(as_Bool_action);
	asBoolAction.setNamed("*value");
	cmd("as").child("Bool").setAction(1, asBoolAction);
	Action asStringAction(as_String_action);
	asStringAction.setNamed("*value");
	cmd("as").child("String").setAction(1, asStringAction);
}
