#include "Lizzy.hpp"

Lizzy::LizzyInterpreter Lizzy::LizzyInterpreter::lizzyi = Lizzy::LizzyInterpreter();

Lizzy::LizzyInterpreter::LizzyInterpreter() : Lizzy::Package("Lizzy"), Interpreter()
{
	LOAD_ONCE
	addDependance(Lizzy::Info::info);
	addDependance(Lizzy::Std::std);
}

void Lizzy::LizzyInterpreter::init()
{
	LOAD_ONCE
	try
	{
		loadDependances();
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
}
