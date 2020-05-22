#include "LizzyLang.hpp"

using namespace Lizzy;



_def_action(LangPkg::run_action)
{
	string filename = args("file");
	auto results = Interpreter().launchFile(filename);
	string buf;
	for(auto r : results)
	{
		buf += r + " ";
	}
	if(buf.size()) buf.pop_back();
	else buf = " ";
	return buf;
}


LangPkg::LangPkg() : Package("Lang")
{
	CALL_ONCE
	addSubPackage(new MemPkg());
}

void LangPkg::load()
{
	CALL_ONCE
	loadSubPackages();

	Action runAction(run_action);
	runAction.setNamed("file");
	cmd("run").setAction(1, runAction);

}
