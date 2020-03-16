#include "LizzyPackage.hpp"

Lizzy::Package::Package(string name) : name(name)
{
	cout << "Package created: " << name << endl;
}

Lizzy::Package::~Package()
{
	unload();
	cout << "Package " << getName() << " unloaded" << endl;
}

void Lizzy::Package::addSubPackage(Package& pkg)
{
	cout << "Dependance of " + getName() + " : " << pkg.getName() << endl;
	subPackages.push_back(&pkg);
}

void Lizzy::Package::loadSubPackages()
{
	for(Package *pkg : subPackages)
	{
		pkg->load();
	}
}

Command& Lizzy::Package::addCommand(string name, bool absolute)
{
	if(not Command::isCommand(name))
	{
		Command *c = new Command(name);
		commands.push_back(c);
		return *c;
	}
	else if(not absolute and not Command::isCommand(getName() + "." +name))
	{
		Command *c = new Command(getName() + "." +name);
		commands.push_back(c);
		return *c;
	}
	throw Exception(name + " Command already exists");
}

bool Lizzy::Package::in(string name) const
{
	for(auto *c : commands)
	{
		if(c->getName() == name) return true;
	}
	return false;
}

Command& Lizzy::Package::getCommand(string name)
{
	for(auto *c : commands)
	{
		if(c->getName() == name) return *c;
	}
	throw Exception(name + " Command already exists");
}

Command& Lizzy::Package::cmd(string name)
{
	if(not in(name)) return addCommand(name);
	return getCommand(name);
}

void Lizzy::Package::unload()
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

void Lizzy::Package::unloadSubPackage(string pkgn)
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

string Lizzy::Package::getName() const
{
	return name;
}
