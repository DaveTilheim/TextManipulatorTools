#include "LizzyInfo.hpp"

using namespace Lizzy;


const string InfoPkg::VERSION = "1.0.0";




_def_action(InfoPkg::version_action)
{
	return InfoPkg::VERSION;
}


InfoPkg::InfoPkg() : Package("Info")
{
	
}

void InfoPkg::load()
{
	CALL_ONCE
	Action versionAction(version_action);
	cmd("version").setAction(0, versionAction);
}
