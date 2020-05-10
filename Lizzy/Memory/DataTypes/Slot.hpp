#ifndef SLOT_HPP
#define SLOT_HPP
#include "Type.hpp"


namespace Lizzy
{
	class Slot : public Reference
	{
	private:
		Data **dataPointer;
	public:
		using Reference::Reference;
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		void setFromData(Data* data) override;
		void setFromValue(string value) override;
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
	};
}


#endif
