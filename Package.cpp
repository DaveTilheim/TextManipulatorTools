#include "Package.hpp"


vector<Package *> Package::packages = vector<Package *>();


Package::Package(string name) : name(name)
{
	//cout << "Package created: " << getName() << endl;
	Package::packages.push_back(this);
}

Package::~Package()
{
	for(auto *cmd : commands)
	{
		delete cmd;
	}
	for(auto *pkg : subPackages)
	{
		delete pkg;
	}
	commands.clear();
	subPackages.clear();
	//cout << "Package destroyed: " << getName() << endl;
}


bool Package::isPackage(string pkgn)
{
	for(auto *pkg : packages)
	{
		if(pkg->getName() == pkgn) return true;
	}
	return false;
}

Package& Package::getPackage(string pkgn)
{
	if(isPackage(pkgn))
	{
		for(auto *pkg : packages)
		{
			if(pkg->getName() == pkgn)
				return *pkg;
		}
	}
	throw Exception(pkgn + " is not a Package");
}

void Package::reload()
{
	for(auto *c : commands)
	{
		Command::addCommand(c);
	}
	for(auto *pkg : subPackages)
	{
		pkg->reload();
	}
}

void Package::addSubPackage(Package* pkg)
{
	//cout << "Dependance of " + getName() + " : " << pkg->getName() << endl;
	if(pkg->super) throw Exception(pkg->getName() + " as already a child of a Package");
	subPackages.push_back(pkg);
	pkg->setSuper(this);
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
		if(Command::isCommand(cmd->getName()))
			Command::eraseCommand(cmd->getName());
		if(Command::isCommand(getName()+"."+cmd->getName()))
			Command::eraseCommand(getName()+"."+cmd->getName());
	}
	for(auto *pkg : subPackages)
	{
		pkg->unload();
	}
}

void Package::unloadSubPackage(string pkgn)
{
	int i = 0;
	for(auto *pkg : subPackages)
	{
		if(pkg->getName() == pkgn)
		{
			pkg->unload();
			break;
		}
		i++;
	}
}

string Package::getName() const
{
	if(super) return super->getName() + "." + name;
	return name;
}

void Package::setSuper(const Package *pkg)
{
	super = pkg;
}

Command& Package::cmdAlias(Command& c, string aliasName, bool global, bool local)
{
	if(global)
		c.alias(aliasName);
	if(local)
		c.alias(getName() + "." + aliasName);
	return c;
}

Command& Package::cmdCpy(Command& c, string aliasName, bool global, bool local)
{
	if(local)
	{
		Command &cc = addCommand(getName() + "." + aliasName);
		cc.alias(c);
		if(global)
		{
			cc.alias(aliasName);
		}
		return cc;
	}
	throw Exception("A Command must be global and/or local");
}
