#ifndef LIZZY_LANG_MEM_HPP
#define LIZZY_LANG_MEM_HPP
#include "LizzyStdIo.hpp"
#include "Memory/MemoryContext.hpp"


namespace Lizzy
{
	class MemPkg : public Package
	{
	public:
		static MemoryContext *_memoryContext; //to delete before static deletion
		static MemoryContext& memoryContext;
	protected:
		_decl_action(new_action)
		_decl_action(set_action)
		_decl_action(get_action)
		_decl_action(type_action)
		_decl_action(exists_action)
	public:
		MemPkg();
		~MemPkg();
		void load() override;
	};
	
	typedef MemPkg Mem;
}

#endif
