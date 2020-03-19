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


IoPkg::IoPkg() : Package("Io")
{

}

void IoPkg::load()
{
	CALL_ONCE
	Action printAction(print_action);
	Action printlnAction(println_action);

	cmd("print").setAction(-1, printAction);
	cmd("println").setAction(-1, printlnAction);
}
