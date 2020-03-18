#include "Lizzy/Lizzy.hpp"
#include "Interpreter.hpp"

using namespace Lizzy;

int main(int argc, char const *argv[])
{
	LizzyPkg lizzyPkg;
	
	try
	{
		//lizzyPkg.load();
		cout <<"---------------------------------------" << endl;
		lizzyPkg.lizzyInt.launchFile("main.lz");
		cout <<"---------------------------------------" << endl;
		for(auto pkg : Package::packages)
		{
			cout << pkg->getName() << endl;
		}
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
	
	
	return 0;
}
