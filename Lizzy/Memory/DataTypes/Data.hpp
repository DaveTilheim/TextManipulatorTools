#ifndef LIZZY_DATA_HPP
#define LIZZY_DATA_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include "../../../Exception.hpp"

#define _dup_in_method

using namespace std;

#define CONST_CONTROL if(this->getAttr() & (int)CONST_A) throw Exception("Data is marked const. It can not be modified");
#define REF_CONST_CONTROL if(this->getSlotAttr() & (int)CONST_A) throw Exception("Data is marked const. It can not be modified");
#define CONST_CONTROL_(data) if((data)->getAttr() & (int)CONST_A) throw Exception("Data is marked const. It can not be modified");
#define RESTRICT_CONTROL(data) if((data)->getAttr() & (int)RESTRICT_A) throw Exception("Data is marked restrict. It can not be referenced");
#define TRY_DELETE(data) if(((data)->getAttr() & PERSISTANT_A) == 0)\
						{\
							delete data;data=nullptr;\
						}\

#define TRY_SLOT_DELETE(slot) if(((*slot)->getAttr() & PERSISTANT_A) == 0)\
						{delete *slot; *slot = nullptr;delete slot;slot=nullptr;}\



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
		static Data *(*generateInteger)(int);
		static Data *(*generateFloat)(double);
		static Data *(*generateBool)(bool);
		static Data *(*generateString)(string);
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
		static bool isInteger(string value);
		static bool isFloat(string value);
		static bool isBool(string value);
	};
}



#endif
