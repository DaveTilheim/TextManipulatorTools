#ifndef LIZZY_INFO_HPP
#define LIZZY_INFO_HPP
#include "../Command.hpp"
#include "LizzyPackage.hpp"


namespace Lizzy
{
	class InfoPkg final : public Package
	{
	protected:
		_decl_action(version_action)
	protected:
		static const string VERSION;
		void load() override;
	public:
		static InfoPkg info;
		InfoPkg();
	};
}

#endif
