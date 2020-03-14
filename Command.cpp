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

string Command::exe(Tokens& args) noexcept
{
	int nargs = args.partialSize();
	if(nargs)
	{
		string child = args.getCurrent();
		if(isChild(child))
		{
			args.next();
			return getChild(child).exe(args);
		}
	}

	if(actions.find(nargs) == actions.end())
	{
		return actions[-1]->run(args);
	}

	return actions[nargs]->run(args);
}

string Command::exe(string sargs) noexcept
{
	Tokens args = sargs;
	return exe(args);
}

void Command::check(string sargs) noexcept(false)
{
	Tokens args = sargs;
	check(args);
}

void Command::check(Tokens& args) noexcept(false)
{
	int nargs = args.partialSize();
	if(nargs)
	{
		string child = args.getCurrent();
		if(isChild(child))
		{
			args.next();
			getChild(child).check(args);
			return;
		}
	}
	if(actions.find(nargs) == actions.end())
	{
		if(actions.find(-1) == actions.end())
		{
			throw Exception("No action for " + to_string(nargs) + " number of arguments for '" + getFullName() + "' Command");
		}
	}
}

ostream& operator<<(ostream& out, const Command& self)
{
	return out << self.getFullName();
}
