#ifndef LIZZY_VECTOR_HPP
#define LIZZY_VECTOR_HPP
#include "Data.hpp"
#include <vector>

namespace Lizzy
{
	class Vector : public Data
	{
	private:
		vector<Data *> value;
	public:
		Vector();
		Vector(const Vector& cp) _dup_in_method;
		~Vector();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		Data *get(int i) const noexcept(false);
		void add(Data &data) _dup_in_method;
		void remove(int i) noexcept(false);
		void clean();
		void foreach(void (*operation)(Data *));
		vector<Data *>& getVector();
		void set(Data& data, int i) noexcept(false) _dup_in_method;
		void copyVector(const vector<Data *>& vec);
		Vector& operator=(const Vector& cp);
	};
}


#endif
