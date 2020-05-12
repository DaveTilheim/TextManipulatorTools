#ifndef LIZZY_DATA_HPP
#define LIZZY_DATA_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include "../../../Exception.hpp"

#define _dup_in_method

using namespace std;




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


	class Data
	{
	protected:
		static Data *(*generateInteger)(int);
		static Data *(*generateFloat)(double);
		static Data *(*generateBool)(bool);
		static Data *(*generateString)(string);
	public:
		virtual ~Data();
		virtual string toString() = 0;
		virtual string type();
		virtual Types typeId();
		virtual Data *dup();
		virtual void setFromData(Data* data); //cast Data
		virtual void setFromValue(string value); //cast value
		static bool isInteger(string value);
		static bool isFloat(string value);
		static bool isBool(string value);
	};
}



#endif
