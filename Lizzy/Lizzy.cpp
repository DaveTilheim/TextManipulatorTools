#include "Lizzy.hpp"


//Interpreter Lizzy::LizzyPkg::lizzyInt = Interpreter();
Interpreter *Lizzy::LizzyPkg::pLizzyInt = nullptr;

_def_pre(Lizzy::LizzyPkg::load_package_1)
{
	string pkg = args("name");
	Package::getPackage(pkg).load();
	return pkg;
}

_def_pre(Lizzy::LizzyPkg::load_package_0)
{
	args.namedArgList["name"] = "Lizzy";
	return Lizzy::LizzyPkg::load_package_1(args);
}

_def_pre(Lizzy::LizzyPkg::load_symbol_commentary)
{
	for(auto symbol : args.list())
	{
		pLizzyInt->setCommentarySymbol(symbol);
	}
	return to_string(args.list().size());
}


Lizzy::LizzyPkg::LizzyPkg() : Package("Lizzy")
{
	CALL_ONCE
	pLizzyInt = &lizzyInt;
	lizzyInt.setCommentarySymbol("//");
	addSubPackage(new Lizzy::InfoPkg());
	addSubPackage(new Lizzy::StdPkg());
	addSubPackage(new Lizzy::LangPkg());

	Action load_package_0Action(load_package_0);
	Action load_package_1Action(load_package_1);
	Action loadSymbolCommentaryAction(load_symbol_commentary);
	load_package_1Action.setNamed("name");

	lizzyInt.preIntCommand("load").child("package").setAction(0, load_package_0Action);
	lizzyInt.preIntCommand("load").child("package").setAction(1, load_package_1Action);
	lizzyInt.preIntCommand("load").child("symbol").child("commentary").setAction(-1, loadSymbolCommentaryAction);
}

void Lizzy::LizzyPkg::load()
{
	CALL_ONCE
	loadSubPackages();

}
