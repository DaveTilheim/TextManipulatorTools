#include "Action.hpp"


Action::Action(const Action& other) : func(other.getFunction()), namedArgs(other.getNamed()), separator(other.getSeparator())
{

}

Action::Action(function<string(Args)> func, string separator) : func(func), separator(separator)
{

}

const function<string(Args)>& Action::getFunction() const
{
	return func;
}

const vector<string>& Action::getNamed() const
{
	return namedArgs;
}

string Action::getSeparator() const
{
	return separator;
}

void Action::setNamed(string name)
{
	if(not nameExists(name))
	{
		namedArgs.push_back(name);
	}
}

Action& Action::named(string name)
{
	if(nameExists(name)) return *this;
	setNamed(name);
	return *this;
}

bool Action::nameExists(string name) const
{
	for(auto n : namedArgs)
	{
		if(n == name) return true;
	}
	return false;
}

string Action::run(Tokens args)
{
	unordered_map<string, string> namedContent;
	Tokens sequArgs;
	for(auto n : namedArgs)
	{
		namedContent[n] = "unused";
	}
	while(not args.oob())
	{
		String elem = args;
		if(elem == getSeparator())
		{
			sequArgs.push_back(elem);
		}
		else
		{
			auto splitString = elem.split(getSeparator());
			if(nameExists(splitString[0]))
			{
				if(splitString.size() == 2)
					namedContent[splitString[0]] = splitString[1];
				else
					namedContent[splitString[0]] = "used";
			}
			else
			{
				elem.unpack("["); //surround command / subcommand / named parameter
				sequArgs.push_back(elem);
			}
		}
	}
	Args_t actionArgs(sequArgs, namedContent);
	return func(actionArgs);
}

int Action::namedNumber(const Tokens& args) const
{
	auto size = args.size();
	int counter = 0;
	for(int i = args.getIndex(); i < size; i++)
	{
		if(nameExists(args[i]))
			counter++;
	}
	return counter;
}

Action& Action::operator=(const Action& other)
{
	func = other.getFunction();
	namedArgs = other.getNamed();
	return *this;
}

ostream& operator<<(ostream& out, const Action& action)
{
	return out;
}
