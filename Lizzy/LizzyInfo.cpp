#include "LizzyInfo.hpp"

using namespace Lizzy;

InfoPkg InfoPkg::info = InfoPkg();

const string InfoPkg::VERSION = "1.0.0";




_def_action(InfoPkg::version_action)
{
	return InfoPkg::VERSION;
}





InfoPkg::InfoPkg() : Package("Info")
{
	LOAD_ONCE
}

void InfoPkg::load()
{
	LOAD_ONCE
	Action versionAction(version_action);
	cmd("version").setAction(0, versionAction);
}
