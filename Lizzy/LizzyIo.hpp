#ifndef LIZZY_IO_HPP
#define LIZZY_IO_HPP
#include "../Package.hpp"

namespace Lizzy
{
	class IoPkg : public Package
	{
	protected:
		_decl_action(print_action)
		_decl_action(println_action)
	public:
		IoPkg();
		void load() override;
	};

	typedef IoPkg Io;
}

#endif
