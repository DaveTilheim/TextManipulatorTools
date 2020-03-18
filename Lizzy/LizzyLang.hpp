#ifndef LIZZY_LANG_HPP
#define LIZZY_LANG_HPP
#include "LizzyIo.hpp"


namespace Lizzy
{
	class LangPkg : public Package
	{
	protected:
		
	public:
		LangPkg();
		void load() override;
	};
	
	typedef LangPkg Lang;
}

#endif
