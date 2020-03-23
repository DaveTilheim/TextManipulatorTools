#ifndef LIZZY_STD_IO_HPP
#define LIZZY_STD_IO_HPP
#include "../Package.hpp"
#include "LizzyLangMem.hpp"

namespace Lizzy
{
	class IoPkg : public Package
	{
	protected:
		_decl_action(print_action)
		_decl_action(println_action)
		_decl_action(printm_action)
		_decl_action(printmln_action)
	public:
		IoPkg();
		void load() override;
	};

	typedef IoPkg Io;
}

#endif
