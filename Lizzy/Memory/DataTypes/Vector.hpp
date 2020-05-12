#ifndef LIZZY_VECTOR_HPP
#define LIZZY_VECTOR_HPP
#include "Slot.hpp"
#include <vector>

namespace Lizzy
{
	class Vector : public Data
	{
	private:
		vector<Slot *> value;
	public:
		Vector();
		Vector(const Vector& cp) _dup_in_method;
		Vector(Data *data);
		Vector(vector<Slot *>&);
		~Vector();
		void clean();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		Slot *get(int i) const noexcept(false);
		void add(Slot *data);
		void foreach(void (*operation)(Slot *));
		vector<Slot *>& getVector();
		void setFromData(Data *data) override;
		void setFromValue(string value) override;
		void copyVector(const vector<Slot *>& vec);
		Vector& operator=(const Vector& cp);
	};
}


#endif
