#ifndef ACTION_HPP
#define ACTION_HPP
#include "Tokens.hpp"
#include <map>
#include <functional>

struct Args_t
{
	Tokens argList;
	map<string, string> namedArgList;
	Args_t(Tokens& argList, const map<string, string>& namedArgList) : argList(argList), namedArgList(namedArgList) {}
	string operator[](string name)
	{
		if(namedArgList.find(name) == namedArgList.end()) return "null";
		return namedArgList[name];
	}
	string operator[](int i) { return argList[i]; }
	Tokens& list() { return argList; }
	inline string use(string name, int i=0)
	{
		return (*this)[name] == "unused" ? (*this)[i] : (*this)[name];
	}
	inline string operator()(string name, int i=0)
	{
		return use(name, i);
	}
};

typedef Args_t& Args;

class Action
{
private:
	function<string(Args)> func;
	vector<string> namedArgs;
	const string separator;
public:
	Action() = delete;
	Action(const Action& other);
	Action(function<string(Args)> func, string separator="=");
	const function<string(Args)>& getFunction() const;
	const vector<string>& getNamed() const;
	string getSeparator() const;
	void setNamed(string name);
	bool nameExists(string name) const;
	int namedNumber(const Tokens& args) const;
	string run(Tokens args);
	Action& operator=(const Action& other);
	friend ostream& operator<<(ostream& out, const Action& action);
};

#endif
