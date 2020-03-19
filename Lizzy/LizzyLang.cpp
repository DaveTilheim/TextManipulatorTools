#include "LizzyLang.hpp"

using namespace Lizzy;


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
