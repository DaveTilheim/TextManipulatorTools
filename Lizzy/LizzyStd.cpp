#include "LizzyStd.hpp"


Lizzy::Std Lizzy::Std::std = Std();

Lizzy::Std::Std() : Lizzy::Package("Std")
{
	LOAD_ONCE
}

void Lizzy::Std::init()
{
	LOAD_ONCE
}
