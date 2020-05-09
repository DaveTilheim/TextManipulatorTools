#ifndef LIZZY_REFERENCE_HPP
#define LIZZY_REFERENCE_HPP
#include "Data.hpp"
#include <ctype.h>

namespace Lizzy
{
	class Reference : public Data
	{
	private:
		Data **dataPointer;
	public:
		Reference();
		Reference(Reference& other);
		Reference(string strvalue);
		Reference(Data *data);
		Reference(Data **data);
		~Reference();
		int getAttr() override;
		void setAttr(int attr) override;
		virtual string toString() override;
		virtual string type() override;
		virtual Types typeId() override;
		virtual Data *dup() override;
		virtual void set(Data* data) override;
		void set(Data** data);
		virtual Data *get();
		Data **getSlot();
		bool isEmpty() const;
		int getSlotAttr() const;
		void setSlotAttr(int attr);
		Reference& operator=(Reference& other);
	};
}


#endif
