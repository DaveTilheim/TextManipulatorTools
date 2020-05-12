#ifndef SLOT_HPP
#define SLOT_HPP
#include "Data.hpp"
namespace Lizzy
{
	enum SlotAttributes
	{
		REFERENCE_A = 0x1,
		PERSISTANT_A= 0x2,
		RESTRICT_A  = 0x4,
		FINAL_A     = 0x8,
		CONST_A		= 0x16
	};

	struct Slot
	{
		Data **data = nullptr;
		int attribs = 0x0;
		Slot(Data **data);
		~Slot();
		bool isReference();
		bool isPersistant();
		bool isDeleteable();
		bool isRestrict();
		bool isFinal();
		bool isConst();
		void tryDelete();
	};
}


#endif
