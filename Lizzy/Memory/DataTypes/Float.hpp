#ifndef LIZZY_FLOAT_HPP
#define LIZZY_FLOAT_HPP
#include "Integer.hpp"
#include "String.hpp"
#include "Bool.hpp"
#include "Vector.hpp"
#include "Table.hpp"
#include "Reference.hpp"

namespace Lizzy
{
	class Float : public Data
	{
	private:
		double value;
	public:
		Float(double value=0.f);
		Float(string expr);
		Float(const Float& cp);
		Float(Data *data);
		~Float();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		double get() const;
		void set(double newValue);
		void setFromData(Data *data) override;
		void setFromValue(string value) override;
		Float& operator=(const Float& cp);
	};
}


#endif
