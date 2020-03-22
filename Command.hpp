#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Action.hpp"
#include "Exception.hpp"
#include <unordered_map>
#include <cstdlib>

struct Attributes
{
	bool root = false;
	int nargs = -2;
};

#define PermCommand static Command

class Command
{
protected:
	static unordered_map<string, Command *> commandList;
	string name;
	const Command *super;
	unordered_map<int, Action *> actions;
	vector<Command *> childs;
	bool isAlias = false;
public:
	static void eraseCommand(string name);
	static bool isCommand(string name);
	static Command& getCommand(string name);
	static Attributes extractAttributes(String& commandName);
	static Command& addCommand(Command *cmd);
	Command() = delete;
	Command(const Command& other);
	Command(string name, const Command *super=nullptr);
	~Command();
	Command& alias(const Command& cmd);
	Command& alias(string otherName);
	Command& child(string childname);
	string getName() const;
	virtual string getFullName() const;
	const Command& getSuper() const;
	const unordered_map<int, Action *>& getActions() const;
	const vector<Command *>& getChilds() const;
	Command& getChild(string name);
	int getMaximumNargs() const;
	Action& getAction(Tokens& args);
	Command& setAction(int nargs, const Action& action);
	void setChild(string name);
	void setSuper(const Command *super);
	bool isChild(string name) const;
	string action(string args="") noexcept;
	string run(string args="", int forceNargs=-2);
	virtual string run(Tokens& args, int forceNargs=-2);
	void rename(string name);
	Command& operator=(const Command& other) = delete;
	friend ostream& operator<<(ostream& out, const Command& self);
};

class IndependantCommand : public Command
{
public:
	IndependantCommand(string name);
	string run(Tokens& args, int forceNargs=-2) override;
	void setChild(string name);
	string getFullName() const override;
};



#endif
