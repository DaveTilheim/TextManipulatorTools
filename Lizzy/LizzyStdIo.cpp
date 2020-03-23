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

	cmd("print").setAction(-1, printAction);
	cmd("println").setAction(-1, printlnAction);
	cmd("printm").setAction(-1, printmAction);
	cmd("printmln").setAction(-1, printmlnAction);
}
