#include "Lizzy.hpp"

Interpreter Lizzy::LizzyPkg::lizzyInt = Interpreter();
Lizzy::LizzyPkg Lizzy::LizzyPkg::lizzyPkg = Lizzy::LizzyPkg();

Lizzy::LizzyPkg::LizzyPkg() : Package("Lizzy")
{
	LOAD_ONCE
	Lizzy::LizzyPkg::lizzyInt.setCommentarySymbol("//");
	addSubPackage(Lizzy::InfoPkg::info);
	addSubPackage(Lizzy::StdPkg::std);
}

void Lizzy::LizzyPkg::load()
{
	LOAD_ONCE

	loadSubPackages();

}
