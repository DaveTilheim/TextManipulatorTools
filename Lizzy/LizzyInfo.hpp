#ifndef LIZZY_INFO_HPP
#define LIZZY_INFO_HPP
#include "../Command.hpp"
#include "../Package.hpp"


namespace Lizzy
{
	class InfoPkg : public Package
	{
	private:
		static const string VERSION;
	protected:
		_decl_action(version_action)
	public:
		InfoPkg();
		void load() override;
	};

	typedef InfoPkg Info;
}

#endif
