#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "DataTypes/Type.hpp"
#include "../../String.hpp"
#include <ctype.h>
#include <unordered_map>
#include <iomanip>
#include <vector>

using namespace std;

namespace Lizzy
{
	enum SetModes
	{
		FORB,
		CAST,
		FULL
	};

	typedef unordered_map<string, Data **> StackMemory;
	typedef unordered_map<string, string> ReferencesMemory;
	typedef vector<Data **> PersistantMemory;

	class Memory
	{
	public:
		const string id;
		StackMemory stack;
		ReferencesMemory references;
		static PersistantMemory persistant;
		Memory *parent = nullptr;
		Memory *child = nullptr;
	public:
		Memory(Memory *parent, string id);
		~Memory();
		void traceMemory();
	public:
		Data **findStack(string id);
		Data **find(string id);
		Memory *getDownMemory();
		Memory *getUpMemory();
		Memory *getMemoryWhereIs(string id);
		void push(string id);
		void pop();
		void deleteData(string id);
		void deletePersistantData(Data **ref);
	public:
		//persistantMemory
		static Data **getPersistantDataSlot(Data *data);
		static void erasePersistantMemory();
		//
		vector<string> toAccessor(string id);
		bool isAccessor(string id);
		bool isAccessor(Data *data);
		Data *getDataFromAccessor(string expr);
		Data **getDataSlotFromAccessor(string expr);
		bool exists(string id);
		bool existsGlobalUp(string id);
		Data *getDataGlobalUp(string id);
		Data **getDataSlotGlobalUp(string id);
		string getReferenceGlobalUp(string id);
		void setAttr(string id, int attr);
		string getId(Data *);
		string getId();
		Data **inferReference(string id);
		int getDataSize(string id);
		//Generic primitive
		void addPrimitiveData(string id, string strGenValue);
		Data **generateDataFromValue(string value);
		Data **generateDataFromId(string id);
		//Specific Data
		Data **generateInteger(Data* value);
		Data **generateInteger(string value);
		Data **generateFloat(Data* value);
		Data **generateFloat(string value);
		Data **generateBool(Data* value);
		Data **generateBool(string value);
		Data **generateString(Data *value);
		Data **generateString(string value);
		Data **generateReference(string value);
		Data **generateReference(Data **value);
		Data **generatePersistantReference(string value);
		Data **generateDataSlotPersistant(string value);
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
		//containers
		Data **generateVector(vector<string>& values);
		void addVector(string id, vector<string>& values);
		Data **generateTable(string value);
		void addTable(string id, string value);
		//String
		string getCharAt(string id, string index);
		void setCharAt(string id, string index, string character);
		//casting
		void cast(Data *to, Data *from);
		void cast(Data *to, string from);
		static bool isAllowedTypeFrom(Types t1, Types t2);
		static bool isAllowedNumberFrom(Types otherType);
		static bool isAllowedStringFrom(Types otherType);
		//reference
		void changeReference(string id, string value);
		//Memory controls
		void attr_persistant_control(Data *data);
		void attr_const_control(string id, bool refmode=false);
		SetModes attr_final_control(Data *data, Types otherType, bool refmode=false);
		void attr_set_control(Data *data, int attr);
		void addAttr(Data *data, int attr);
		//
		void field(string, string);
	public: //command bridge
		string new_primitive(string id, string value);
		string new_Integer(string id, string value);
		string new_Float(string id, string value);
		string new_Bool(string id, string value);
		string new_String(string id, string value);
		string new_Reference(string id, string value);
		string new_Vector(string id, vector<string>& values);
		string new_Table(string id, string value);
		string set_memory(string id, string value);
		string set_reference(string id, string value);
		string get_memory(string id);
		string add_attribute(string id, int attr);
		string type_memory(string id);
		string exists_memory(string id);
		string size_memory(string id);
		string get_char_at(string id, string index);
		string set_char_at(string id, string index, string character);
		string del_data(string id);
		string del_persistant_data(string id);
		string field_memory(string id, string value);
	};
}


#endif
