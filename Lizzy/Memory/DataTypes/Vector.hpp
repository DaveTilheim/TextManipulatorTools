#ifndef LIZZY_VECTOR_HPP
#define LIZZY_VECTOR_HPP
#include "Reference.hpp"
#include <vector>

namespace Lizzy
{
	class Vector : public Data
	{
	private:
		vector<Data **> value;
	public:
		Vector();
		Vector(const Vector& cp) _dup_in_method;
		Vector(Data *data);
		Vector(vector<Data **>&);
		~Vector();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		Data **get(int i) const noexcept(false);
		void add(Data **data);
		void clean();
		void foreach(void (*operation)(Data **));
		vector<Data **>& getVector();
		void setFromData(Data *data) override;
		void setFromValue(string value) override;
		void copyVector(const vector<Data **>& vec);
		Vector& operator=(const Vector& cp);
	};
}


#endif
