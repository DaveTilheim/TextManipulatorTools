#ifndef LIZZY_LANG_MEM_HPP
#define LIZZY_LANG_MEM_HPP
#include "LizzyStdIo.hpp"
#include "Memory/MemoryContext.hpp"


namespace Lizzy
{
	class MemPkg : public Package
	{
	private:
		static MemoryContext *_memoryContext; //to delete before static deletion
		static MemoryContext& memoryContext;
	protected:
		_decl_action(new_action)
		_decl_action(news_action)
		_decl_action(set_action)
		_decl_action(get_action)
		_decl_action(get_2_action)
		_decl_action(gets_action)
		_decl_action(type_action)
		_decl_action(add_action)
	public:
		MemPkg();
		~MemPkg();
		void load() override;
	};
	
	typedef MemPkg Mem;
}

#endif
