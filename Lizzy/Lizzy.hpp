#ifndef LIZZY_HPP
#define LIZZY_HPP
#include "LizzyStd.hpp"
#include "LizzyInfo.hpp"
#include "../Interpreter.hpp"


namespace Lizzy
{
	class LizzyPkg final : public Package
	{
	public:
		LizzyPkg();
		void load() override;
		static LizzyPkg lizzyPkg;
		static Interpreter lizzyInt;
	};
}





#endif
