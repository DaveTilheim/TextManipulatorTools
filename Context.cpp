#include "Context.hpp"

unordered_map<string, Command *> *Context::current = nullptr;
unordered_map<string, unordered_map<string, Command *>> Context::contexts = unordered_map<string, unordered_map<string, Command *>>();
string Context::id = string();


bool Context::exists(string id)
{
	return Context::contexts.find(id) != Context::contexts.end();
}

void Context::create(string id)
{
	if(not exists(id))
		Context::contexts[id] = unordered_map<string, Command *>();
	else
		throw Exception(id + " context already exists");
}

void Context::erase(string id)
{
	if(exists(id))
		Context::contexts.erase(id);
	else
		throw Exception(id + " context not exists");
}

void Context::set(string id)
{
	if(exists(id))
	{
		Context::id = id;
		current = &Context::contexts[id];
	}
	else
		throw Exception(id + " context not exists");
}

void Context::use(string id)
{
	if(not exists(id))
		Context::contexts[id] = unordered_map<string, Command *>();
	current = &Context::contexts[id];
	Context::id = id;
}

unordered_map<string, Command *>& Context::get(string id)
{
	if(exists(id))
		return Context::contexts[id];
	else
		throw Exception(id + " context not exists");
}

unordered_map<string, Command *>& Context::get()
{
	return *Context::current;
}

string Context::getId()
{
	return id;
}

