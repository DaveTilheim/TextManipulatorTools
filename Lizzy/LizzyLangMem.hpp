#ifndef LIZZY_LANG_MEM_HPP
#define LIZZY_LANG_MEM_HPP
#include "LizzyStdIo.hpp"
#include "Memory/Memory.hpp"


namespace Lizzy
{
	class MemPkg : public Package
	{
	public:
		static Memory *_memoryContext; //to delete before static deletion
		static Memory& memoryContext;
	protected:
		//variables
		_decl_action(new_action)
		_decl_action(new_Integer_action)
		_decl_action(new_Float_action)
		_decl_action(new_Bool_action)
		_decl_action(new_String_action)
		_decl_action(new_Reference_action)
		_decl_action(new_Integer_action_1)
		_decl_action(new_Float_action_1)
		_decl_action(new_Bool_action_1)
		_decl_action(new_String_action_1)
		_decl_action(new_Reference_action_1)
		_decl_action(to_reference_action)
		_decl_action(to_reference_action_1)
		//containers
		_decl_action(new_Vector_action)
		_decl_action(new_Table_action)
		_decl_action(new_Table_action_1)
		_decl_action(field_action);
		_decl_action(field_action_0);
		_decl_action(size_action);
		//String
		_decl_action(set_char_action)
		_decl_action(get_char_action)
		//qualifiers
		_decl_action(const_action)
		_decl_action(final_action)
		_decl_action(restrict_action)
		_decl_action(persistant_action);
		//accessors
		_decl_action(set_action)
		_decl_action(set_reference_action)
		_decl_action(get_action)
		//introspection
		_decl_action(type_action)
		_decl_action(exists_action)
		_decl_action(trace_memory_action)
		//branchs
		_decl_action(push_action)
		_decl_action(pop_action);
		_decl_action(del_action)
		_decl_action(del_persistant_action)
	public:
		MemPkg();
		~MemPkg();
		void load() override;
	};
	
	typedef MemPkg Mem;
}

#endif
