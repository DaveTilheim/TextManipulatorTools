#ifndef LIZZY_INFO_HPP
#define LIZZY_INFO_HPP
#include "../Command.hpp"
#include "LizzyPackage.hpp"


namespace Lizzy
{
	class LizzyI;

	class Info final : public Package
	{
	private:
		static string version_action(Args);
		static const string VERSION;
		void init() override;
		friend class LizzyI;
	public:
		static Info info;
		Info();
	};
}

#endif
