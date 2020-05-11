#ifndef SLOT_HPP
#define SLOT_HPP
#include "Type.hpp"


namespace Lizzy
{
	class Slot : public Reference
	{
	public:
		using Reference::Reference;
		~Slot();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		/*void setFromData(Data* data) override;
		void setFromValue(string value) override;*/
		void setData(Data *data);
		void setData(string value);
		void toReference(Data **data);
		void toReference(string value);
		Data *get() override;
		Slot& operator=(Slot& other);
		operator Data*();
		operator Bool*();
		operator Float*();
		operator Integer*();
		operator Reference*();
		operator String*();
		operator Table*();
		operator Vector*();
		static Data *generatePrimitive(string value);
		static Data **generateSlotPrimitive(string value);
	};
}


#endif
