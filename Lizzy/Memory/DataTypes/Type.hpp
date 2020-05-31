#ifndef TYPE_HPP
#define TYPE_HPP
#include "Bool.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Table.hpp"
#include "Vector.hpp"
#include "Slot.hpp"
#include "../../../String.hpp"

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
		string operation(string v1, string (*ope)(Data *));
		string operation(Slot *v1, string (*ope)(Data *));
		string add(Data *v1, Data *v2);
		string sub(Data *v1, Data *v2);
		string mul(Data *v1, Data *v2);
		string div(Data *v1, Data *v2);
		string mod(Data *v1, Data *v2);
		string land(Data *v1, Data *v2);
		string lor(Data *v1, Data *v2);
		string lxor(Data *v1, Data *v2);
		string lnot(Data *v1);
		string pre_inc(Data *v1);
		string post_inc(Data *v1);
		string pre_dec(Data *v1);
		string post_dec(Data *v1);
		string cand(Data *v1, Data *v2);
		string cor(Data *v1, Data *v2);
		string cnot(Data *v1);
		string rshift(Data *v1, Data *v2);
		string lshift(Data *v1, Data *v2);
		string equal(Data *v1, Data *v2);
		string not_equal(Data *v1, Data *v2);
		string lesser(Data *v1, Data *v2);
		string bigger(Data *v1, Data *v2);
		string cast(Data *d, Types type);
		inline string boolean(bool value) { return value ? "true" : "false"; }
		bool evaluate(Data *d);
		bool evaluate(string v);
	}
}


#endif
