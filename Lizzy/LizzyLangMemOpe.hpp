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
		_decl_action(mod_action);
		_decl_action(land_action);
		_decl_action(lor_action);
		_decl_action(lxor_action);
		_decl_action(lnot_action);
		_decl_action(pre_inc_action);
		_decl_action(post_inc_action);
		_decl_action(pre_dec_action);
		_decl_action(post_dec_action);
		_decl_action(and_action);
		_decl_action(or_action);
		_decl_action(not_action);
		_decl_action(rshift_action);
		_decl_action(lshift_action);
		_decl_action(ternary_action);
		_decl_action(equal_action);
		_decl_action(not_equal_action);
		_decl_action(lesser_action);
		_decl_action(bigger_action);
		//cast
		_decl_action(as_Integer_action);
		_decl_action(as_Float_action);
		_decl_action(as_Bool_action);
		_decl_action(as_String_action);
	public:
		OpePkg(Memory *mc);
		void load() override;
	};
}

#endif
