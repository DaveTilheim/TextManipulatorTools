#ifndef LIZZY_HPP
#define LIZZY_HPP
#include "LizzyStd.hpp"
#include "LizzyInfo.hpp"
#include "LizzyLang.hpp"
#include "../Interpreter.hpp"


namespace Lizzy
{
	class LizzyPkg final : public Package
	{
	protected:
		
		_decl_pre(load_package_1)
		_decl_pre(load_package_0)
		_decl_pre(load_symbol_commentary)
		_decl_pre(use_file_action)
		_decl_action(int_action)
	public:
		LizzyPkg();
		void load() override;
		Interpreter lizzyInt;
		static Interpreter *pLizzyInt;
	};
}





#endif
