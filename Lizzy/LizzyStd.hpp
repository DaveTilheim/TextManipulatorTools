#ifndef LIZZY_STD_HPP
#define LIZZY_STD_HPP
#include "../Command.hpp"
#include "LizzyPackage.hpp"


namespace Lizzy
{
	class StdPkg final : public Package
	{
	protected:
		_decl_action(alias_action)
		_decl_action(print_action)
		_decl_action(println_action)
	protected:
		void load() override;
	public:
		static StdPkg std;
		StdPkg();
	};
}

#endif
