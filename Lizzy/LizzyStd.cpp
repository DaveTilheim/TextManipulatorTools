#include "LizzyStd.hpp"

using namespace Lizzy;

_def_action(StdPkg::reload_package_action)
{
	string pkg = args("name");
	Package::getPackage(pkg).reload();
	return pkg;
}

_def_action(StdPkg::unload_package_action)
{
	string pkg = args("name");
	Package::getPackage(pkg).unload();
	return pkg;
}

_def_action(StdPkg::load_package_action)
{
	string pkg = args("name");
	Package::getPackage(pkg).load();
	return pkg;
}

_def_action(StdPkg::alias_action)
{
	Command *cmd = nullptr;
	if(args.list().size() < 2) throw ("alias command must have at least two args");
	string newname = args.list();
	while(not args.list().oob())
	{
		string cname = args.list();
		if(not cmd) cmd = &Command::getCommand(cname);
		else cmd = &cmd->getChild(cname);
	}
	if(cmd) cmd->alias(newname);
	return newname;
}



StdPkg::StdPkg() : Package("Std")
{
	addSubPackage(new IoPkg());
}

void StdPkg::load()
{
	CALL_ONCE
	loadSubPackages();
	Action aliasAction(alias_action);
	Action unload_packageAction(unload_package_action);
	unload_packageAction.setNamed("name");
	Action reload_packageAction(reload_package_action);
	reload_packageAction.setNamed("name");
	Action load_packageAction(load_package_action);
	load_packageAction.setNamed("name");

	cmd("alias").setAction(-1, aliasAction);
	cmd("unload").child("package").setAction(1, unload_packageAction);
	cmd("reload").child("package").setAction(1, reload_packageAction);
	cmd("load").child("package").setAction(1, load_packageAction);
}
