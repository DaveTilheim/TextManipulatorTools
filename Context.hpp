#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <unordered_map>
#include <string>
#include "Exception.hpp"

using namespace std;

class Command;

class Context
{
private:
	static string id;
	static unordered_map<string, Command *> *current;
	static unordered_map<string, unordered_map<string, Command *>> contexts;
public:
	static bool exists(string id);
	static void create(string id);
	static void set(string id);
	static void use(string id);
	static void erase(string id);
	static unordered_map<string, Command *>& get(string id);
	static unordered_map<string, Command *>& get();
	static string getId();
};


#endif
