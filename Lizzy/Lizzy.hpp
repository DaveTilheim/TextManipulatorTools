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
	public:
		LizzyPkg();
		void load() override;
		Interpreter lizzyInt;
	};
}





#endif
