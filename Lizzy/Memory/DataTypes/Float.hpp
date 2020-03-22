#ifndef LIZZY_FLOAT_HPP
#define LIZZY_FLOAT_HPP
#include "Data.hpp"

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
		~Float();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		double get() const;
		void set(double newValue);
		Float& operator=(const Float& cp);
	};
}


#endif
