#ifndef LIZZY_HPP
#define LIZZY_HPP
#include "LizzyStd.hpp"
#include "LizzyInfo.hpp"
#include "../Interpreter.hpp"


namespace Lizzy
{
	class LizzyInterpreter final : public Package, public Interpreter
	{
	public:
		LizzyInterpreter();
		void init() override;
		static LizzyInterpreter lizzyi;
	};
}





#endif
