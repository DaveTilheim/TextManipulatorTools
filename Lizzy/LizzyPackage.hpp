#ifndef LIZZY_PACKAGE_HPP
#define LIZZY_PACKAGE_HPP
#include "../Command.hpp"

using namespace std;

#define LOAD_ONCE static bool loaded=false; if(loaded) throw Exception(getName() + " Package already loaded"); loaded=true;

#define _decl_action(name) static string name(Args args);
#define _def_action(fullname) string fullname(Args args)

namespace Lizzy
{
	class Package
	{
	private:
		string name;
		vector<Package *> subPackages;
		vector<Command *> commands;
	protected:
		Package(string name);
		virtual ~Package();
		void addSubPackage(Package& pkg);
		void loadSubPackages();
		void unload();
		void unloadSubPackage(string pkg);
		virtual void load() = 0;
		string getName() const;
		bool in(string) const;
		Command& getCommand(string name);
		Command& addCommand(string name, bool absolute=false);
		Command& cmd(string name);
	};
}

#endif
