#include "Command.hpp"




int main(int argc, char const *argv[])
{
	Command add("add");
	add.setAction(2, Action([](Args args)
	{
		return to_string((int) args.list() + (int) args.list());
	}));

	cout << add.run("5 10 test error") << endl;

	return 0;
}
