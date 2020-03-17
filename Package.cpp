#include "Package.hpp"

Package::Package(string name) : name(name)
{
	cout << "Package created: " << name << endl;
}

Package::~Package()
{
	unload();
	cout << "Package " << getName() << " unloaded" << endl;
}

void Package::addSubPackage(Package& pkg)
{
	cout << "Dependance of " + getName() + " : " << pkg.getName() << endl;
	subPackages.push_back(&pkg);
}

void Package::loadSubPackages()
{
	for(Package *pkg : subPackages)
	{
		pkg->load();
	}
}

Command& Package::addCommand(string name, bool global, bool local)
{
	Command *c = nullptr;
	if(not global and not local) throw Exception("pkg@"+getName() + " ==> " + "When added into a package, the " + name + " Command must be global and/or local");
	if(global)
	{
		if(not Command::isCommand(name))
		{
			c = new Command(name);
			commands.push_back(c);
		}
		else
		{
			throw Exception("pkg@"+getName() + " ==> " + name + " Command already exists as global (try define it as local)");
		}
	}

	if(local)
	{
		if(not Command::isCommand(getName() + "." +name))
		{
			if(c)
			{
				c->alias(getName() + "." + name);
			}
			else
			{
				c = new Command(getName() + "." + name);
				commands.push_back(c);
			}
		}
		else
		{
			throw Exception("pkg@"+getName() + " ==> " + getName() + "." + name + " Command already exists as local");
		}
	}
	
	return *c;
}

bool Package::in(string name) const
{
	for(auto *c : commands)
	{
		if(c->getName() == name) return true;
	}
	return false;
}

Command& Package::getCommand(string name)
{
	for(auto *c : commands)
	{
		if(c->getName() == name) return *c;
	}
	throw Exception("pkg@"+getName() + " ==> " + name + " Command already exists");
}

Command& Package::cmd(string name, bool global, bool local)
{
	if(not in(name)) return addCommand(name, global, local);
	return getCommand(name);
}

void Package::unload()
{
	for(auto *cmd : commands)
	{
		Command::eraseCommand(cmd->getName());
		delete cmd;
	}
	for(auto *pkg : subPackages)
	{
		pkg->unload();
	}
	commands.clear();
	subPackages.clear();
}

void Package::unloadSubPackage(string pkgn)
{
	int i = 0;
	for(auto *pkg : subPackages)
	{
		if(pkg->getName() == pkgn)
		{
			pkg->unload();
			subPackages.erase(subPackages.begin() + i);
			break;
		}
		i++;
	}
}

string Package::getName() const
{
	return name;
}
