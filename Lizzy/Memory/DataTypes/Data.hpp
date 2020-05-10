#ifndef LIZZY_DATA_HPP
#define LIZZY_DATA_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include "../../../Exception.hpp"

#define _dup_in_method

using namespace std;

#define CONST_CONTROL if(getAttr() & (int)CONST_A) throw Exception("Data is marked const. It can not be modified");

namespace Lizzy
{
	enum Types
	{
		NONE_T,
		INTEGER_T,
		FLOAT_T,
		BOOL_T,
		STRING_T,
		REFERENCE_T,
		VECTOR_T,
		TABLE_T,
		CLASS_T,
		OBJECT_T,
		SLOT_T
	};

	enum DataAttributes
	{
		CONST_A = 0x0001,
		FINAL_A = 0x0002,
		RESTRICT_A = 0x0004,
		PERSISTANT_A = 0x0008
	};

	string getAttrAsString(int attr);

	class Data
	{
	protected:
		int attr = 0;
	public:
		virtual ~Data();
		virtual string toString() = 0;
		virtual int getAttr();
		virtual void setAttr(int attr);
		virtual string type();
		virtual Types typeId();
		virtual Data *dup();
		virtual void setFromData(Data* data); //cast Data
		virtual void setFromValue(string value); //cast value
		bool hasAttr(DataAttributes attr);
	};
}



#endif
