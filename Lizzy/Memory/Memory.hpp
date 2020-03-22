#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "DataTypes/Integer.hpp"
#include "DataTypes/Float.hpp"
#include "DataTypes/Bool.hpp"
#include "DataTypes/String.hpp"
#include "DataTypes/Vector.hpp"
#include <ctype.h>
#include <map>

using namespace std;

namespace Lizzy
{
	class Memory : private map<string, Data *>
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
		void setData(string id, string strGenValue);
		Data *getData(string id);
		string getType(string id);
		string toString(string id);
		static Types type(string constStrGenValue);
		static string inferType(string constStrGenValue);
		string new_primitive(string id, string value);
	};
}


#endif
