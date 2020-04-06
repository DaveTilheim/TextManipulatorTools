#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "DataTypes/Integer.hpp"
#include "DataTypes/Float.hpp"
#include "DataTypes/Bool.hpp"
#include "DataTypes/String.hpp"
#include "DataTypes/Vector.hpp"
#include "DataTypes/Reference.hpp"
#include "../../String.hpp"
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
	public:
		const string id;
		Memory& self;
		Memory *parent;
		Memory *child = nullptr;
	public:
		Memory(Memory *parent, string id);
		~Memory();
	public:
		Memory *getDownMemory();
		void push(string id);
		void pop();
	public:
		bool exists(string id);
		bool existsGlobalUp(string id);
		Data *getDataGlobalUp(string id);
		Data **getDataSlotGlobalUp(string id);
		void setAttr(string id, int attr);
		string getId(Data *);
		string getId();
		Data **inferReference(string id);
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
		void setDataFromId(string id, string value);
		void setData(string id, string value);
		Data *getData(string id);
		string getType(string id);
		string toString(string id);
		static Types type(string constStrGenValue);
		static string inferType(string constStrGenValue);
		//containers
		Vector *generateVector(vector<string>& values);
		void addVector(string id, vector<string>& values);
		int getVectorSize(string id);
		//String
		string getCharAt(string id, string index);
		void setCharAt(string id, string index, string character);
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
		void castInVector(Vector *ref, string value);
		static bool isAllowedTypeFrom(Types t1, Types t2);
		static bool isAllowedNumberFrom(Types otherType);
		static bool isAllowedStringFrom(Types otherType);
		//reference
		void changeReference(string id, string value);
		void toReference(string id, string value);
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
		string new_Vector(string id, vector<string>& values);
		string set_memory(string id, string value);
		string set_reference(string id, string value);
		string get_memory(string id);
		string add_attribute(string id, int attr);
		string type_memory(string id);
		string exists_memory(string id);
		string to_reference(string id, string value);
		string size_vector(string id);
		string get_char_at(string id, string index);
		string set_char_at(string id, string index, string character);
	};
}


#endif
