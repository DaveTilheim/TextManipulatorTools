#ifndef TYPE_HPP
#define TYPE_HPP
#include "Bool.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Reference.hpp"
#include "String.hpp"
#include "Table.hpp"
#include "Vector.hpp"


namespace Lizzy
{
	namespace Type
	{
		Types Memory::type(string constStrGenValue);
		string Memory::inferType(string constStrGenValue);
	}
}


#endif