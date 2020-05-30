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
	try
	{
		Package::getPackage(pkg).load();
	}
	catch(const PackageAlreadyExistsException& e)
	{
		//cout << "%%ignore load " << pkg << endl;
	}
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


_def_action(StdPkg::load_context_action)
{
	string context = args("id");
	Context::set(context);
	return context;
}

_def_action(StdPkg::load_extern_context_action)
{
	string context = args("id");
	Context::create(context);
	return context;
}

_def_action(StdPkg::load_command_to_context_action)
{
	string command = args("command");
	string context = args("context", 1);
	cout << command << " " << context << endl;
	Command::getCommand(command).forceLoad(context);
	return command + " => " + context;
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


	Action loadContext(load_context_action);
	loadContext.setNamed("id");
	cmd("load").child("context").setAction(1, loadContext);

	Action loadExternContext(load_extern_context_action);
	loadExternContext.setNamed("id");
	cmd("load").child("extern").child("context").setAction(1, loadExternContext);

	Action loadCommandToContextAction(load_command_to_context_action);
	loadCommandToContextAction.setNamed("command");
	loadCommandToContextAction.setNamed("context");
	cmd("load").child("command").child("to").child("context").setAction(2, loadCommandToContextAction);




}
