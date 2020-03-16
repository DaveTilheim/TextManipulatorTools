#include "LizzyPackage.hpp"

Lizzy::Package::Package(string name) : name(name)
{
	cout << "Package created: " << name << endl;
}

void Lizzy::Package::addDependance(Package& pkg)
{
	cout << "Dependance of " + getName() + " : " << pkg.getName() << endl;
	dependances.push_back(&pkg);
}

void Lizzy::Package::loadDependances()
{
	for(Package *pkg : dependances)
	{
		try
		{
			pkg->init();
		}
		catch(const Exception& e)
		{
			cout << e.what() << endl;
		}
	}
}

string Lizzy::Package::getName() const
{
	return name;
}
