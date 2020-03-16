#include "Lizzy/Lizzy.hpp"
#include "Interpreter.hpp"

using namespace Lizzy;

int main(int argc, char const *argv[])
{
	try
	{
		LizzyPkg::lizzyPkg.load();
		LizzyPkg::lizzyInt.launchFile("main.lz");
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
	
	
	return 0;
}
