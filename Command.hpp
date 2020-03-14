#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Action.hpp"
#include "Exception.hpp"
#include <map>
#include <cstdlib>

struct Attributes
{
	bool root = false;
	int nargs = -2;
};

class Command final
{
private:
	const string name;
	const Command *super;
	map<int, Action *> actions;
	vector<Command *> childs;
public:
	Command() = delete;
	Command(const Command& other);
	Command(string name, const Command *super=nullptr);
	~Command();
	string getName() const;
	string getFullName() const;
	const Command& getSuper() const;
	const map<int, Action *>& getActions() const;
	const vector<Command *>& getChilds() const;
	Command& getChild(string name);
	Action& getAction(Tokens& args);
	void setAction(int nargs, const Action& action);
	void setChild(string name);
	void setSuper(const Command *super);
	bool isChild(string name) const;
	string action(string args="") noexcept;
	string run(string args="", int forceNargs=-2);
	string run(Tokens& args, int forceNargs=-2);
	Attributes extractAttributes(String& commandName) const;
	Command& operator=(const Command& other) = delete;
	friend ostream& operator<<(ostream& out, const Command& self);
};

#endif
