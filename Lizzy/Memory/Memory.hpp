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
		//Generic primitive
		void addPrimitiveData(string id, string strGenValue);
		Data *generateDataFromValue(string value);
		Data *generateDataFromId(string id);
		//Specific Data
		Integer *generateInteger(string value);
		Integer *generateFloat(string value);
		Integer *generateBool(string value);
		Integer *generateString(string value);
		void addInteger(string id, string value);
		void addFloat(string id, string value);
		void addBool(string id, string value);
		void addString(string id, string value);
		//set primitive
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
		string new_Integer(string id, string value);
		string new_Float(string id, string value);
		string new_Bool(string id, string value);
		string new_String(string id, string value);
		template <class T> string new_specific(string id, string value);
		string set_memory(string id, string value);
		string get_memory(string id);
		static string value_type_memory(string value);
		string data_type_memory(string id);
	};
}


#endif
