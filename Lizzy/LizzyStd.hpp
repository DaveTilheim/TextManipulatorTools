#ifndef LIZZY_STD_HPP
#define LIZZY_STD_HPP
#include "../Command.hpp"
#include "LizzyPackage.hpp"


namespace Lizzy
{
	class LizzyI;

	class Std final : public Package
	{
	private:
		void init() override;
		friend class LizzyI;
	public:
		static Std std;
		Std();
	};
}

#endif
