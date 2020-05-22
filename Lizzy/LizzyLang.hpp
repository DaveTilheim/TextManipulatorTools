#ifndef LIZZY_LANG_HPP
#define LIZZY_LANG_HPP
#include "../Package.hpp"
#include "../Interpreter.hpp"
#include "LizzyLangMem.hpp"


namespace Lizzy
{
	class LangPkg : public Package
	{
	protected:
		_decl_action(run_action)
	public:
		LangPkg();
		void load() override;
	};
	
	typedef LangPkg Lang;
}

#endif
