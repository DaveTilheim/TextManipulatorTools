#include "Lizzy.hpp"



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


Lizzy::LizzyPkg::LizzyPkg() : Package("Lizzy")
{
	CALL_ONCE
	Lizzy::LizzyPkg::lizzyInt.setCommentarySymbol("//");
	addSubPackage(new Lizzy::InfoPkg());
	addSubPackage(new Lizzy::StdPkg());
	addSubPackage(new Lizzy::LangPkg());

	Action load_package_0Action(load_package_0);
	Action load_package_1Action(load_package_1);
	load_package_1Action.setNamed("name");

	lizzyInt.preIntCommand("load").child("package").setAction(0, load_package_0Action);
	lizzyInt.preIntCommand("load").child("package").setAction(1, load_package_1Action);
}

void Lizzy::LizzyPkg::load()
{
	CALL_ONCE
	loadSubPackages();

}
