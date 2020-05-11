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
	for(auto it : value)
	{
		TRY_SLOT_DELETE(it.second);
	}
	value.clear();
}

string Table::toString()
{
	string buf;
	for(auto it : value)
	{
		buf += it.first + ":" + (*it.second)->toString() + " ";
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

Data **Table::get(string id) noexcept(false)
{
	if(value.find(id) == value.end()) throw Exception("key: " + id + " not exists for the current table");
	return value[id];
}


void Table::foreach(void (*operation)(Data **))
{
	for(auto it : value)
	{
		operation(it.second);
	}
}

void Table::copyTable(const unordered_map<string, Data **>& table)
{
	CONST_CONTROL
	value.clear();
	for(auto it : table)
	{
		value[it.first] = new Data*((*it.second)->dup());
	}
}

unordered_map<string, Data **>& Table::getTable()
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
