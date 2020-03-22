#ifndef LIZZY_STD_HPP
#define LIZZY_STD_HPP
#include "LizzyStdIo.hpp"



namespace Lizzy
{
	class StdPkg : public Package
	{
	protected:
		_decl_action(reload_package_action)
		_decl_action(unload_package_action)
		_decl_action(load_package_action)
		_decl_action(alias_action)
	public:
		StdPkg();
		void load() override;
	};
	
	typedef StdPkg Std;
}

#endif
