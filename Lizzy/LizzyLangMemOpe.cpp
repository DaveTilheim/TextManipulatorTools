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
}
