#include "Lizzy/Lizzy.hpp"

using namespace Lizzy;

int main(int argc, char const *argv[])
{
	try
	{
		LizzyInterpreter::lizzyi.init();
		LizzyInterpreter::lizzyi.launchFile("main.lz");
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
	
	
	return 0;
}
