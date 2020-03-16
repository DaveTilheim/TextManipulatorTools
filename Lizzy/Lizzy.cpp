#include "Lizzy.hpp"

Interpreter Lizzy::LizzyPkg::lizzyInt = Interpreter();
Lizzy::LizzyPkg Lizzy::LizzyPkg::lizzyPkg = Lizzy::LizzyPkg();

Lizzy::LizzyPkg::LizzyPkg() : Lizzy::Package("LizzyPkg")
{
	LOAD_ONCE
	Lizzy::LizzyPkg::lizzyInt.setCommentarySymbol("//");
	addSubPackage(Lizzy::InfoPkg::info);
	addSubPackage(Lizzy::StdPkg::std);
}

void Lizzy::LizzyPkg::load()
{
	LOAD_ONCE
	try
	{
		loadSubPackages();
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
}
