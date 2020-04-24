#include "Table.hpp"


using namespace Lizzy;



Table::Table()
{

}

Table::Table(const Table& cp)
{
	copyTable(cp.value);
}

Table::~Table()
{
	for(auto it : value)
	{
		if((it.second->getAttr() & PERSISTANT_A) == 0)
		{
			cout  << "del " << it.second->type() <<endl;
			delete it.second;
		}
	}
	value.clear();
}

string Table::toString()
{
	string buf;
	for(auto it : value)
	{
		buf += it.first + ":" + it.second->toString() + " ";
	}
	if(buf.size()) buf.pop_back();
	else return " ";
	return buf;
}

string Table::type()
{
	return "Table";
}

Types Table::typeId()
{
	return TABLE_T;
}

Data *Table::dup()
{
	return new Table(*this);
}

Data *Table::get(string id) noexcept(false)
{
	if(value.find(id) == value.end()) throw Exception("key: " + id + " not exists for the current table");
	return value[id];
}

Data **Table::getAddr(string id) noexcept(false)
{
	if(value.find(id) == value.end()) throw Exception("key: " + id + " not exists for the current table");
	return &value[id];
}

void Table::set(Data& newData, string id) noexcept(false)
{
	value[id] = newData.dup();
}

void Table::remove(string id) noexcept(false)
{
	if(value.find(id) == value.end()) throw Exception("key: " + id + " not exists for the current table");
	delete value[id];
	value.erase(id);
}


void Table::foreach(void (*operation)(Data *))
{
	for(auto it : value)
	{
		operation(it.second);
	}
}

void Table::copyTable(const unordered_map<string, Data *>& table)
{
	value.clear();
	for(auto it : table)
	{
		value[it.first] = it.second->dup();
	}
}

unordered_map<string, Data *>& Table::getTable()
{
	return value;
}

Table& Table::operator=(const Table& cp)
{
	copyTable(cp.value);
	return *this;
}
