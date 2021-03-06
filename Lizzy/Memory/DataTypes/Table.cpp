#include "Table.hpp"


using namespace Lizzy;



Table::Table()
{

}

Table::Table(const Table& cp)
{
	copyTable(cp.value);
}

Table::Table(Data *data)
{
	setFromData(data);
}

Table::~Table()
{
	clean();
}

void Table::clean()
{
	for(auto it : value)
	{
		delete it.second;
	}
	value.clear();
}

string Table::toString()
{
	string buf;
	for(auto it : value)
	{
		buf += it.first + ":" + (*it.second->get())->toString() + " ";
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

Slot *Table::get(string id) noexcept(false)
{
	if(value.find(id) == value.end()) throw Exception("key: " + id + " not exists for the current table");
	return value[id];
}


void Table::foreach(void (*operation)(Slot *))
{
	for(auto it : value)
	{
		operation(it.second);
	}
}

void Table::copyTable(const unordered_map<string, Slot *>& table)
{
	clean();
	for(auto it : table)
	{
		value[it.first] = new Slot(new Data*((*it.second->get())->dup()));
	}
}

unordered_map<string, Slot *>& Table::getTable()
{
	return value;
}

Table& Table::operator=(const Table& cp)
{
	copyTable(cp.value);
	return *this;
}

void Table::setFromData(Data *data)
{
	if(dynamic_cast<Table *>(data))
	{
		*this = *dynamic_cast<const Table *>(data);
	}
	else
	{
		throw Exception("Can not convert " + data->type() + " into Table");
	}
}

void Table::setField(string name, Slot *dvalue)
{
	if(value.find(name) == value.end())
	{
		value[name] = dvalue;
	}
	else
	{
		throw Exception(name + " field already exists for the current Table");
	}
}
