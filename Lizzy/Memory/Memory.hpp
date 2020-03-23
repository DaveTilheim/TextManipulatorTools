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
	class Memory : private unordered_map<string, Data *>
	{
	private:
		Memory& self;
	public:
		Memory();
		~Memory();
		bool exists(string id);
		void addIntegerData(string id, string stri);
		void addFloatData(string id, string strf);
		void addBoolData(string id, string strb);
		void addStringData(string id, string strs);
		void addPrimitiveData(string id, string strGenValue);
		void addCopyData(string id, string cpId);
		void setIntegerData(string id, string stri);
		void setFloatData(string id, string strf);
		void setBoolData(string id, string strb);
		void setStringData(string id, string strs);
		void setPrimitiveData(string id, string strGenValue);
		void setCopyData(string id, string cpId);
		Data *generateCopyOf(string id);
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
