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

	struct DataAttributes
	{
		bool _const : 1 = false;
		bool _strict : 1 = false;
	};

	class Data
	{
	private:
		DataAttributes attr;
	public:
		virtual ~Data();
		virtual string toString() = 0;
		DataAttributes& getAttr();
		void setAttr(const DataAttributes& attr);
		virtual string type();
		virtual Types typeId();
		virtual Data *dup();
	};
}



#endif
