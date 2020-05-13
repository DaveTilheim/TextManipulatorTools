#include "LizzyInfo.hpp"

using namespace Lizzy;


const string InfoPkg::VERSION = "1.0.0";




_def_action(InfoPkg::version_action)
{
	return InfoPkg::VERSION;
}

_def_action(InfoPkg::packages_action)
{
	string buf;
	for(Package *pkg : Package::packages)
	{
		buf += pkg->getName() + " | ";
	}
	buf.pop_back();
	buf.pop_back();
	buf.pop_back();
	return buf;
}


InfoPkg::InfoPkg() : Package("Info")
{
	
}

void InfoPkg::load()
{
	CALL_ONCE
	Action versionAction(version_action);
	cmd("version").setAction(0, versionAction);

	Action packagesAction(packages_action);
	cmd("packages").setAction(0, packagesAction);
}
