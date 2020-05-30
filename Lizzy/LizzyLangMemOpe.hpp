#ifndef LIZZY_LANG_MEM_OPE_HPP
#define LIZZY_LANG_MEM_OPE_HPP
#include "Memory/Memory.hpp"
#include "../Package.hpp"

namespace Lizzy
{
	class OpePkg : public Package
	{
	private:
		static Memory *memoryContext;
		_decl_action(add_action);
		_decl_action(sub_action);
		_decl_action(mul_action);
		_decl_action(div_action);
	public:
		OpePkg(Memory *mc);
		void load() override;
	};
}

#endif
