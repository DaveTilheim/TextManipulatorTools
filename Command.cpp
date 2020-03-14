#include "Command.hpp"


map<string, Command *> Command::commandList = map<string, Command *>();


Command::Command(const Command& other)
: Command(other.getName(), &other.getSuper())
{
	actions = other.getActions();
	childs = other.getChilds();
}

Command::Command(string name, const Command *super) : name(name), super(super)
{
	if(not super) //!!!!
		Command::commandList[name] = this;
}

Command::~Command()
{
	for(auto *cmdit : childs)
	{
		delete cmdit;
	}
	for(auto it : actions)
	{
		delete it.second;
	}
}

string Command::getName() const
{
	return name;
}

string Command::getFullName() const
{
	if(super)
		return super->getFullName() + "." + getName();
	return getName();
}

const Command& Command::getSuper() const
{
	return *super;
}

const map<int, Action *>& Command::getActions() const
{
	return actions;
}

const vector<Command *>& Command::getChilds() const
{
	return childs;
}

Command& Command::getChild(string name)
{
	for(auto *cmdit : childs)
	{
		if(cmdit->getName() == name)
		{
			return *cmdit;
		}
	}
	throw Exception("No child named '" + name + "' for '" + getFullName() + "' Command");
}

Action& Command::getAction(Tokens& args)
{
	int nargs = args.size();
	if(actions.find(nargs) != actions.end())
	{
		return *actions[nargs];
	}
	throw Exception("No action takes " + to_string(nargs) + " number of parameters for '" + getFullName() + "' Command");
}

int Command::getMaximumNargs() const
{
	int maxi = -2;
	for(auto it : actions)
	{
		maxi = it.first;
	}
	return maxi;
}

void Command::setAction(int nargs, const Action& action)
{
	actions[nargs] = new Action(action);
}

void Command::setChild(string name)
{
	for(auto *cmdit : childs)
	{
		if(cmdit->getName() == name)
		{
			throw Exception("'" + name + "' child already exists for '" + getFullName() + "' Command");
		}
	}
	childs.push_back(new Command(name, this));
}

void Command::setSuper(const Command *superc)
{
	super = superc;
}

bool Command::isChild(string name) const
{
	for(const auto *cmdit : childs)
	{
		if(cmdit->getName() == name)
			return true;
	}
	return false;
}

string Command::action(string sargs) noexcept
{
	Tokens args = sargs;
	int nargs = args.size();
	if(actions.find(nargs) == actions.end())
	{
		return actions[-1]->run(args);
	}
	return actions[nargs]->run(args);
}

string Command::run(Tokens& args, int forceNargs)
{
	int nargs = args.partialSize();
	if(forceNargs > -2) // si un nombre d'argument est imposé
	{
		if(nargs < forceNargs) // si le nombre imposé n'est pas respecté
		{
			throw Exception(to_string(nargs) + " given but expected " + to_string(forceNargs));
		}
		nargs = forceNargs;
	}
	else
	{
		if(nargs > getMaximumNargs()) // mise à niveau du nombre d'arguments afin de ne pas dépasser de la commande courrante
			nargs = getMaximumNargs();
	}

	Tokens arguments;
	if(nargs) // cas d'une commande possédant des arguments
	{
		String element = args.getCurrent();
		Attributes attributes = Command::extractAttributes(element);
		if(forceNargs == -2 and not attributes.root and isChild(element)) //commande fille
		{
			args.next();
			return getChild(element).run(args, attributes.nargs);
		}

		int i = 0;
		while(i < nargs) //parcourir les nargs arguments de la commande
		{
			args.next();
			if(Command::isCommand(element)) //si on détecte une commande root
			{
				cout << "ROOT" << endl;
				string ret = getCommand(element).run(args, attributes.nargs);
				arguments.push_back(ret);
			}
			else //si on détecte une constante
			{
				arguments.push_back(element);
			}
			element = args.getCurrent();
			attributes = Command::extractAttributes(element);
			i++;
		}
	}

	if(actions.find(nargs) == actions.end()) //si pas de prototype
	{
		if(actions.find(-1) != actions.end()) //si prototype indéfinit
		{
			return actions[-1]->run(arguments);
		}
		else
		{
			throw Exception(getFullName() + " has no function which takes " + to_string(nargs) + " parameters");
		}
	}
	cout << "CALL" << endl;
	return actions[nargs]->run(arguments); //execution classique
}

string Command::run(string sargs, int forceNargs)
{
	Tokens args = sargs;
	return run(args, forceNargs);
}


Attributes Command::extractAttributes(String& commandName)
{
	int i;
	Attributes attr;
	if((i = commandName.find(":")) != string::npos)
	{
		string name = commandName.substr(0, i);
		String attributes = commandName.substr(i);
		if(attributes != ":")
			attributes.erase(0, 1);
		commandName = name;
		attributes.remove(".");
		if(attributes.size())
		{
			if(attributes.find("root") != string::npos)
			{
				attr.root = true;
				attributes.remove("root");
			}
			if(attributes.size())
			{
				attr.nargs = atoi(attributes.c_str());
			}
		}
	}
	return attr;
}

ostream& operator<<(ostream& out, const Command& self)
{
	return out << self.getFullName();
}


bool Command::isCommand(string name)
{
	return commandList.find(name) != commandList.end();
}

Command& Command::getCommand(string name)
{
	return *commandList[name];
}

vector<string> Command::launch(string expr)
{
	Tokens exprTok = expr;
	vector<string> ret;
	while(not exprTok.oob())
	{
		String commandName = exprTok;
		Attributes attributes = Command::extractAttributes(commandName);
		ret.push_back(Command::getCommand(commandName).run(exprTok, attributes.nargs));
	}
	return ret;
}



