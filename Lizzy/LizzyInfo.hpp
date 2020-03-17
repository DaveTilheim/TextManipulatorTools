#ifndef LIZZY_INFO_HPP
#define LIZZY_INFO_HPP
#include "../Command.hpp"
#include "../Package.hpp"


namespace Lizzy
{
	PKG
	(
		InfoPkg,
		static const string VERSION;
		_decl_action(version_action),
		info
	)
	typedef InfoPkg Info;
}

#endif
