#ifndef LIZZY_TABLE_HPP
#define LIZZY_TABLE_HPP
#include "Slot.hpp"
#include <unordered_map>

namespace Lizzy
{
	class Table : public Data
	{
	private:
		unordered_map<string, Slot *> value;
	public:
		Table();
		Table(const Table& cp) _dup_in_method;
		Table(Data *data);
		~Table();
		void clean();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		Slot *get(string id) noexcept(false);
		void foreach(void (*operation)(Slot *));
		unordered_map<string, Slot *>& getTable();
		void setFromData(Data *data) override;
		void copyTable(const unordered_map<string, Slot *>& vec);
		Table& operator=(const Table& cp);
	};
}


#endif
