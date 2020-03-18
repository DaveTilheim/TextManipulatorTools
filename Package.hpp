#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "Command.hpp"

using namespace std;


#define _decl_action(name) static string name(Args args);
#define _def_action(fullname) string fullname(Args args)
#define _decl_pre(name) static string name(Args args);
#define _def_pre(fullname) string fullname(Args args)

#define CALL_ONCE static bool _once_guard=false; if(_once_guard) throw Exception(getName() + " is already loaded");_once_guard = true;


class Package
{
private:
	const string name;
	const Package *super = nullptr;
	vector<Package *> subPackages;
	vector<Command *> commands;
protected:
	Package(string name);
	virtual ~Package();
public:
	static vector<Package *> packages;
	virtual void load() = 0;
	static bool isPackage(string pkg);
	static Package& getPackage(string pkg);
	void setSuper(const Package *pkg);
	void reload();
	void addSubPackage(Package* pkg);
	void loadSubPackages();
	void unload();
	void unloadSubPackage(string pkg);
	string getName() const;
	bool in(string) const;
	Command& getCommand(string name);
	Command& addCommand(string name, bool global=true, bool local=true);
	Command& cmd(string name, bool global=true, bool local=true);
};


#endif
