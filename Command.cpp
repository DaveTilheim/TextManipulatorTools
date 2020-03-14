#include "Command.hpp"

Command::Command(const Command& other)
: name(other.getName()), super(&other.getSuper()),
  actions(other.getActions()), childs(other.getChilds())
{

}

Command::Command(string name, const Command *super) : name(name), super(super)
{

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
	if(forceNargs > -2)
	{
		if(nargs < forceNargs)
		{
			throw Exception(to_string(nargs) + " given but expected " + to_string(forceNargs));
		}
	}
	if(nargs)
	{
		string element = args.getCurrent();
		if(isChild(element))
		{
			args.next();
			return getChild(element).run(args);
		}
		/*if(isCommand(element))
		{
			args.next();
			string ret = getCommand(element).run(args);
		}*/
	}

	if(actions.find(nargs) == actions.end())
	{
		if(actions.find(-1) != actions.end())
		{
			return actions[-1]->run(args);
		}
		else
		{
			while(--nargs >= 0)
			{
				if(actions.find(nargs) != actions.end())
				{
					return actions[nargs]->run(args);
				}
			}
		}
	}

	return actions[nargs]->run(args);
}

string Command::run(string sargs, int forceNargs)
{
	Tokens args = sargs;
	return run(args, forceNargs);
}


Attributes Command::extractAttributes(String& commandName) const
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
