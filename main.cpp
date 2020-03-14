#include "Command.hpp"




int main(int argc, char const *argv[])
{
	Command add("add");
	add.setAction(2, Action([](Args args)
	{
		cout << "C1 " << args.list() << endl;
		return to_string((int) args.list() + (int) args.list());
	}));
	add.setAction(1, Action([](Args args)
	{
		//cout << "C2" << endl;
		int n = args.list();
		return to_string(n + n);
	}));
	add.setChild("add");
	add.getChild("add").setAction(2, Action([](Args args)
	{
		cout << "C3 " << args.list() << endl;
		return "0";
	}));

	Command test("test");
	test.setAction(0, Action([](Args args)
	{
		return "1000";
	}));

	//cout << add.run("add 3 3 add 3 4") << endl;

	auto ret = Command::launch("add add:root 3 3 add test:root 4");
	for(auto r : ret)
	{
		cout << "> " << r << endl;
	}

	return 0;
}
