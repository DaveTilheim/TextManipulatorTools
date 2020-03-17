#ifndef LIZZY_STD_HPP
#define LIZZY_STD_HPP
#include "../Command.hpp"
#include "../Package.hpp"


namespace Lizzy
{
	PKG
	(
		StdPkg,
		_decl_action(alias_action)
		_decl_action(print_action)
		_decl_action(println_action),
		std
	)
	
	typedef StdPkg Std;
}

#endif
