#include "LizzyStdIo.hpp"

using namespace Lizzy;


_def_action(IoPkg::print_action)
{
	cout << args.list();
	return to_string(args.list().size());
}

_def_action(IoPkg::println_action)
{
	string ret = print_action(args);
	cout << endl;
	return ret;
}

_def_action(IoPkg::printm_action)
{
	auto len = args.list().size();
	while(not args.list().oob())
	{

		string elem = args.list();
		if(MemPkg::memoryContext.exists(elem))
		{
			cout << MemPkg::memoryContext.get_memory(elem);
		}
		else
		{
			cout << elem;
		}
		if(args.list().getIndex() != len) cout << " ";
	}
	return to_string(args.list().size());
}

_def_action(IoPkg::printmln_action)
{
	string ret = printm_action(args);
	cout << endl;
	return ret;
}

_def_action(IoPkg::input_action)
{
	string tmp;
	getline(cin, tmp);
	if(tmp.size() == 0) tmp = " ";
	return tmp;
}

_def_action(IoPkg::input_action_U)
{
	cout << args.list();
	return input_action(args);
}


IoPkg::IoPkg() : Package("Io")
{

}

void IoPkg::load()
{
	CALL_ONCE
	Action printAction(print_action);
	Action printlnAction(println_action);
	Action printmAction(printm_action);
	Action printmlnAction(printmln_action);
	Action inputAction(input_action);
	Action inputActionU(input_action_U);

	cmd("print").setAction(-1, printAction);
	cmd("println").setAction(-1, printlnAction);
	cmd("printm").setAction(-1, printmAction);
	cmd("printmln").setAction(-1, printmlnAction);
	cmd("input").setAction(0, inputAction);
	cmd("input").setAction(-1, inputActionU);
}
