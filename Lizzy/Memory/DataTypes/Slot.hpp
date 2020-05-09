#ifndef SLOT_HPP
#define SLOT_HPP
#include "Type.hpp"


namespace Lizzy
{
	class Slot : public Data
	{
	private:
		Data **dataPointer;
	public:
		Slot();
		Slot(Slot& other);
		Slot(string strvalue);
		Slot(Data *data);
		~Slot();
		int getAttr() override;
		void setAttr(int attr) override;
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		void set(Data* data) override;
		Data *get();
		Data **getSlot();
		bool isEmpty() const;
		int getSlotAttr() const;
		void setSlotAttr(int attr);
		Slot& operator=(Slot& other);
		operator Data*();
		operator Bool*();
		operator Float*();
		operator Integer*();
		operator Reference*();
		operator String*();
		operator Table*();
		operator Vector*();
	};
}


#endif
