#ifndef LIZZY_PACKAGE_HPP
#define LIZZY_PACKAGE_HPP
#include "../Command.hpp"

using namespace std;

#define LOAD_ONCE static bool loaded=false; if(loaded) throw Exception(getName() + " Package already loaded"); loaded=true;
namespace Lizzy
{
	class Package
	{
	private:
		string name;
		vector<Package *> dependances;
	protected:
		Package(string name);
		void addDependance(Package& pkg);
		void loadDependances();
		virtual void init() = 0;
		string getName() const;
	};
}

#endif
