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
		long extractIndex(Slot *slot);
		long extractIndex(string expr);
		void setField(Slot *tableSlot, string fieldname, Slot *value);
		string operation(string v1, string v2, string (*ope)(Data *, Data *));
		string operation(Slot *v1, string v2, string (*ope)(Data *, Data *));
		string operation(string v1, Slot *v2, string (*ope)(Data *, Data *));
		string operation(Slot *v1, Slot *v2, string (*ope)(Data *, Data *));
		string add(Data *v1, Data *v2);
		template <typename T, typename U> string _add(T v1, U v2) { return to_string(v1 + v2); }
		string sub(Data *v1, Data *v2);
		template <typename T, typename U> string _sub(T v1, U v2) { return to_string(v1 - v2); }
		string mul(Data *v1, Data *v2);
		template <typename T, typename U> string _mul(T v1, U v2) { return to_string(v1 * v2); }
		string div(Data *v1, Data *v2);
		template <typename T, typename U> string _div(T v1, U v2) { return to_string(v1 / v2); }
	}
}


#endif
