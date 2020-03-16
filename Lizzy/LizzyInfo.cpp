#include "LizzyInfo.hpp"


Lizzy::Info Lizzy::Info::info = Info();

const string Lizzy::Info::VERSION = "1.0.0";





string Lizzy::Info::version_action(Args args)
{
	cout << "Lizzy version " << Lizzy::Info::VERSION << endl;
	return Lizzy::Info::VERSION;
}





Lizzy::Info::Info() : Lizzy::Package("Info")
{
	LOAD_ONCE
}

void Lizzy::Info::init()
{
	LOAD_ONCE
	PermCommand version("version");
	Action versionAction(version_action);
	version.setAction(0, versionAction);
}
