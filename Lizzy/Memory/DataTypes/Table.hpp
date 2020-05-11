#ifndef LIZZY_TABLE_HPP
#define LIZZY_TABLE_HPP
#include "Reference.hpp"
#include <unordered_map>

namespace Lizzy
{
	class Table : public Data
	{
	private:
		unordered_map<string, Data **> value;
	public:
		Table();
		Table(const Table& cp) _dup_in_method;
		Table(Data *data);
		~Table();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		Data **get(string id) noexcept(false);
		void foreach(void (*operation)(Data **));
		unordered_map<string, Data **>& getTable();
		void setFromData(Data *data) override;
		void copyTable(const unordered_map<string, Data **>& vec);
		Table& operator=(const Table& cp);
	};
}


#endif
