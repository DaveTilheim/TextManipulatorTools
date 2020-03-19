#include "Lizzy/Lizzy.hpp"
#include "Interpreter.hpp"

using namespace Lizzy;

int main(int argc, char const *argv[])
{
	LizzyPkg lizzyPkg;
	cout <<"---------------------------------------" << endl;
	try
	{
		lizzyPkg.lizzyInt.launchFile("main.lz");
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
	cout <<"---------------------------------------" << endl;
	return 0;
}
