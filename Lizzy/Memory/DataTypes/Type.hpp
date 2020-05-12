#ifndef TYPE_HPP
#define TYPE_HPP
#include "Bool.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Table.hpp"
#include "Vector.hpp"
#include "Slot.hpp"

namespace Lizzy
{
	namespace Type
	{
		Types type(string constStrGenValue);
		string inferType(string constStrGenValue);
		Data **generateSlot(Data *data);
		Data *generatePrimitive(string value);
		void updateSlot(Slot *slot, string value);
		void updateSlot(Slot *slot, Data *data);
	}
}


#endif
