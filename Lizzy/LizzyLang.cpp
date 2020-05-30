#include "LizzyLang.hpp"

using namespace Lizzy;

vector<string> Lizzy::LangPkg::usedFiles = vector<string>();

bool Lizzy::LangPkg::isUsed(string filename)
{
	for(string s : Lizzy::LangPkg::usedFiles)
	{
		if(s == filename) return true;
	}
	return false;
}

_def_action(LangPkg::use_file_action)
{
	string filename = args("*file");
	if(not isUsed(filename))
	{
		FileLoader floader(filename);
		Interpreter::getMainFileLoader().insert(floader);
		Lizzy::LangPkg::usedFiles.push_back(filename);
	}
	return filename;
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

}
