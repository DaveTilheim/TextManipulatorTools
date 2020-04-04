#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "DataTypes/Integer.hpp"
#include "DataTypes/Float.hpp"
#include "DataTypes/Bool.hpp"
#include "DataTypes/String.hpp"
#include "DataTypes/Vector.hpp"
#include "DataTypes/Reference.hpp"
#include <ctype.h>
#include <unordered_map>

using namespace std;

namespace Lizzy
{
	enum SetModes
	{
		FORB,
		CAST,
		FULL
	};

	class Memory : private unordered_map<string, Data *>
	{
	private:
		Memory& self;
	public:
		Memory();
		~Memory();
		bool exists(string id);
		void setAttr(string id, int attr);
		string getId(Data *);
		Data **inferReference(string id, string value);
		//Generic primitive
		void addPrimitiveData(string id, string strGenValue);
		Data *generateDataFromValue(string value);
		Data *generateDataFromId(string id);
		//Specific Data
		Integer *generateInteger(Data* value);
		Integer *generateInteger(string value);
		Float *generateFloat(Data* value);
		Float *generateFloat(string value);
		Bool *generateBool(Data* value);
		Bool *generateBool(string value);
		String *generateString(string value);
		Reference *generateReference(string value);
		void addInteger(string id, string value);
		void addFloat(string id, string value);
		void addBool(string id, string value);
		void addString(string id, string value);
		void addReference(string id, string value);
		//set primitive
		void setDataFromValue(string id, string value);
		void setData(string id, string value);
		Data *getData(string id);
		string getType(string id);
		string toString(string id);
		static Types type(string constStrGenValue);
		static string inferType(string constStrGenValue);
		//casting
		void castIn(Data *data, string value);
		void castInInteger(Integer *data, string value);
		void castInFloat(Float *data, string value);
		void castInBool(Bool *data, string value);
		void castInString(String *data, string value);
		void castInReference(Reference *data, string value);
		void castInInteger(Integer *data, Data* value);
		void castInFloat(Float *data, Data* value);
		void castInBool(Bool *data, Data* value);
		static bool isAllowedTypeFrom(Types t1, Types t2);
		static bool isAllowedNumberFrom(Types otherType);
		static bool isAllowedStringFrom(Types otherType);
		//reference
		void changeReference(string id, string value);
		//Memory controls
		void attr_const_control(string id, bool refmode=false);
		SetModes attr_final_control(Data *data, Types otherType, bool refmode=false);
		void attr_set_control(Data *data, int attr);
		void addAttr(Data *data, int attr);
	public: //command bridge
		string new_primitive(string id, string value);
		string new_Integer(string id, string value);
		string new_Float(string id, string value);
		string new_Bool(string id, string value);
		string new_String(string id, string value);
		string new_Reference(string id, string value);
		string set_memory(string id, string value);
		string set_reference(string id, string value);
		string get_memory(string id);
		string add_attribute(string id, int attr);
		static string value_type_memory(string value);
		string data_type_memory(string id);
	};
}


#endif
