#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "DataTypes/Integer.hpp"
#include "DataTypes/Float.hpp"
#include "DataTypes/Bool.hpp"
#include "DataTypes/String.hpp"
#include "DataTypes/Vector.hpp"
#include <ctype.h>
#include <unordered_map>

using namespace std;

namespace Lizzy
{
	enum Operations
	{
		ADD_O,
		SUB_O,
		MUL_O,
		DIV_O
	};

	class Memory : private unordered_map<string, Data *>
	{
	private:
		Memory& self;
	public:
		Memory();
		~Memory();
		bool exists(string id);
		void addPrimitiveData(string id, string strGenValue);
		Data *generateDataFromValue(string value);
		Data *generateDataFromId(string id);
		void setDataFromValue(string id, string value);
		void setDataFromId(string id, string idcp);
		void setData(string id, string value);
		Data *getData(string id);
		string getType(string id);
		string toString(string id);
		static Types type(string constStrGenValue);
		static string inferType(string constStrGenValue);
	public: //command bridge
		string new_primitive(string id, string value);
		string set_memory(string id, string value);
		string get_memory(string id);
		static string value_type_memory(string value);
		string data_type_memory(string id);
	};
}


#endif
