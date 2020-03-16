#include "LizzyStd.hpp"

using namespace Lizzy;

StdPkg StdPkg::std = StdPkg();



_def_action(StdPkg::alias_action)
{
	string oldname = args.list();
	string newname = args.list();
	StdPkg::std.addCommand(newname, true).alias(Command::getCommand(oldname));
	return newname;
}

_def_action(StdPkg::print_action)
{
	cout << args.list();
	return to_string(args.list().size());
}

_def_action(StdPkg::println_action)
{
	string ret = print_action(args);
	cout << endl;
	return ret;
}

StdPkg::StdPkg() : Package("StdPkg")
{
	LOAD_ONCE
}

void StdPkg::load()
{
	LOAD_ONCE
	Action aliasAction(alias_action);
	Action printAction(print_action);
	Action printlnAction(println_action);
	cmd("alias").setAction(2, aliasAction);
	cmd("print").setAction(-1, printAction);
	cmd("println").setAction(-1, printlnAction);
}
