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
		
	public:
		static vector<string> usedFiles;
		static bool isUsed(string filename);
		_decl_action(use_file_action);
		LangPkg();
		void load() override;
	};
	
	typedef LangPkg Lang;
}

#endif
