#include "Command.hpp"




int main(int argc, char const *argv[])
{
	Command print("print");
	print.setAction(-1, Action([](Args args)
	{
		cout << args.list() << endl;
		return "null";
	}));

	print.child("user").setAction(0, Action([](Args args)
	{
		cout << "Hello dear user!" << endl;
		return "";
	}));

	Command puser("puser");
	puser.alias(print.child("user"));

	Command add("add");
	add.setAction(2, Action([](Args args)
	{
		double d = args.list();
		double dd = args.list();
		return to_string(d + dd);
	}));

	Command sub("sub");
	sub.setAction(2, Action([](Args args)
	{
		double d = args.list();
		double dd = args.list();
		return to_string(d - dd);
	}));

	Command mul("mul");
	mul.setAction(2, Action([](Args args)
	{
		double d = args.list();
		double dd = args.list();
		return to_string(d * dd);
	}));

	Command divi("div");
	divi.setAction(2, Action([](Args args)
	{
		double d = args.list();
		double dd = args.list();
		return to_string(d / dd);
	}));


	Command::interpretFile("file.cmd");
	return 0;
}
