#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Tokens.hpp"
#include "Exception.hpp"
#include <map>
#include <functional>
#include <cstdlib>

typedef Tokens Args;

class Command final
{
private:
	const string name;
	const Command *super;
	map<int, function<string(Tokens)>> actions;
	vector<Command *> childs;
public:
	Command() = delete;
	Command(const Command& other);
	Command(string name, const Command *super=nullptr);
	~Command();
	string getName() const;
	string getFullName() const;
	const Command& getSuper() const;
	const map<int, function<string(Tokens)>>& getActions() const;
	const vector<Command *>& getChilds() const;
	Command& getChild(string name);
	function<string(Tokens)> getAction(Tokens& args);
	void setAction(int nargs, function<string(Tokens)> action);
	void setChild(string name);
	void setSuper(const Command *super);
	bool isChild(string name) const;
	string action(string args="") noexcept;
	string exe(string args="") noexcept;
	string exe(Tokens& args) noexcept;
	void check(string args="") noexcept(false);
	void check(Tokens& args) noexcept(false);
	Command& operator=(const Command& other) = delete;
	friend ostream& operator<<(ostream& out, const Command& self);
};

#endif
