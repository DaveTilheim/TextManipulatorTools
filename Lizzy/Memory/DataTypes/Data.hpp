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
		VECTOR_T,
		TABLE_T,
		CLASS_T,
		OBJECT_T
	};

	enum DataAttributes
	{
		CONST_A = 0x0001,
		FINAL_A = 0x0002
	};

	string getAttrAsString(int attr);

	class Data
	{
	private:
		int attr = 0;
	public:
		virtual ~Data();
		virtual string toString() = 0;
		int getAttr();
		void setAttr(int attr);
		virtual string type();
		virtual Types typeId();
		virtual Data *dup();
	};
}



#endif
