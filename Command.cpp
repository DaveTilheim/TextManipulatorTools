#include "Command.hpp"
/*

unordered_map<string, unordered_map<string, Command *>> Command::commandList = unordered_map<string, unordered_map<string, Command *>>();

string Command::currentContext = "MAIN";

void Command::setContext(string context)
{
	currentContext = context;
	if(commandList.find(context) == commandList.end())
		commandList[context] = unordered_map<string, Command *>();
}
*/
Command::Command(const Command& other)
: Command(other.getName(), &other.getSuper())
{
	actions = other.getActions();
	childs = other.getChilds();
}

Command::Command(string name, const Command *super) : name(name), super(super)
{
	load();
	//cout << "Command " << getFullName() << endl; 
}

Command::Command(string name, string context) : name(name), super(nullptr)
{
	load(context);
}

Command::~Command()
{
	if(not isAlias)
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
	//cout << "~Command " << getFullName() << endl; 
}

void Command::load()
{
	if(not super)
	{
		Context::get()[name] = this;
	}
}

void Command::load(string context)
{
	if(not super) //!!!!
	{
		cout << getFullName() << endl;
		Context::get(context)[name] = this;
	}
}

void Command::forceLoad()
{
	Context::get()[name] = this;
}

void Command::forceLoad(string context)
{
	Context::get(context)[name] = this;
}

Command& Command::addCommand(Command *cmd)
{
	if(cmd->super)
	{
		throw Exception("can not add " + cmd->getFullName() + " as global command because it is a child Command of " + cmd->super->getFullName());
	}
	if(not isCommand(cmd->getName()))
	{
		Context::get()[cmd->getName()] = cmd;
	}
	else
	{
		throw Exception(cmd->getName() + " already exists");
	}
	return *cmd;
}

void Command::eraseCommand(string name)
{
	if(Command::isCommand(name))
	{
		Command *cptr = Context::get()[name];
		Context::get().erase(name);
		vector<string> aliases;
		for(auto cmd : Context::get())
		{
			if(cmd.second == cptr)
				aliases.push_back(cmd.first);
		}
		for(auto scmd : aliases)
		{
			Context::get().erase(scmd);
		}
	}
	else
	{
		throw Exception("can not erase " + name + " Command");
	}
}


Command& Command::alias(const Command& cmd)
{
	isAlias = true;
	actions = cmd.getActions();
	childs = cmd.getChilds();
	return *this;
}

Command& Command::alias(string otherName)
{
	if(not isCommand(otherName))
	{
		Context::get()[otherName] = this;
		return *this;
	}
	throw Exception(otherName +  " Command already exists");
}

string Command::getName() const
{
	return name;
}

string Command::getFullName() const
{
	if(super and super != this)
		return super->getFullName() + "." + getName();
	return getName();
}

const Command& Command::getSuper() const
{
	return *super;
}

const unordered_map<int, Action *>& Command::getActions() const
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
	if(actions.find(-1) != actions.end()) return -1;
	for(auto it : actions)
	{
		if(it.first > maxi)
			maxi = it.first;
	}
	return maxi;
}

Command& Command::setAction(int nargs, const Action& action)
{
	actions[nargs] = new Action(action);
	return *this;
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
			throw Exception(getFullName() + " => " + to_string(nargs) + " given but expected " + to_string(forceNargs));
		}
		nargs = forceNargs;
	}
	else
	{
		if(nargs > getMaximumNargs()) // mise à niveau du nombre d'arguments afin de ne pas dépasser de la commande courrante
			nargs = getMaximumNargs();
	}

	Tokens arguments;
	String element = args.getCurrent();
	Attributes attributes;
	if(element.size()) //cas d'une commande fille
	{
		attributes = Command::extractAttributes(element);
		if(forceNargs == -2 and not attributes.root and isChild(element)) //commande fille
		{
			args.next();
			return getChild(element).run(args, attributes.nargs);
		}
	}
	if(nargs) // cas d'une commande possédant des arguments
	{
		int i = 0;
		int ret = nargs;
		if(nargs == -1) nargs = args.partialSize();
		while(i < nargs and not args.oob()) //parcourir les nargs arguments de la commande
		{
			args.next();
			if(Command::isCommand(element)) //si on détecte une commande root
			{
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
		if(ret == -1) nargs = ret;
		else if(forceNargs == -2) nargs = arguments.size();
		else if(nargs != arguments.size())
			throw Exception(getFullName() + " => " + to_string(nargs) + " arguments gived but expected " + to_string(arguments.size()));
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
	if(commandName.find(" ") == string::npos and (i = commandName.find(":")) != string::npos)
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
	return Context::get().find(name) != Context::get().end();
}

Command& Command::getCommand(string name)
{
	if(not Command::isCommand(name)) throw Exception(name + " is not a recognized Command");
	return *Context::get()[name];
}

Command& Command::child(string ch)
{
	if(isChild(ch))
	{
		return getChild(ch);
	}
	setChild(ch);
	return getChild(ch);
}

void Command::rename(string name)
{
	string old = getName();
	if(not super)
	{
		if(not isCommand(name))
		{
			Context::get().erase(old);
			Context::get()[name] = this;
			this->name = name;
		}
	}
}
/*
IndependantCommand::IndependantCommand(string name) : Command(name, this)
{

}

string IndependantCommand::run(Tokens& args, int forceNargs)
{
	int nargs = args.partialSize();

	if(nargs) // cas d'une commande possédant des arguments
	{
		String element = args.getCurrent();
		if(isChild(element)) //commande fille
		{
			args.next();
			return getChild(element).run(args);
		}
	}
	if(actions.find(nargs) == actions.end()) //si pas de prototype
	{
		if(actions.find(-1) != actions.end()) //si prototype indéfinit
		{
			return actions[-1]->run(args);
		}
		else
		{
			throw Exception(getFullName() + " has no function which takes " + to_string(nargs) + " parameters");
		}
	}
	
	return actions[nargs]->run(args); //execution classique
}

void IndependantCommand::setChild(string name)
{
	for(auto *cmdit : childs)
	{
		if(cmdit->getName() == name)
		{
			throw Exception("'" + name + "' child already exists for '" + getFullName() + "' Command");
		}
	}
	IndependantCommand *child = new IndependantCommand(name);
	child->setSuper(this);
	childs.push_back(child);
}

Command& IndependantCommand::child(string childname)
{
	if(isChild(childname))
	{
		return getChild(childname);
	}
	setChild(childname);
	return getChild(childname);
}

string IndependantCommand::getFullName() const
{
	if(super and super != this)
		return super->getFullName() + "." + getName();
	return getName();
}

*/

