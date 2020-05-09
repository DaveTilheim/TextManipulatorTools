#ifndef LIZZY_INTEGER_HPP
#define LIZZY_INTEGER_HPP
#include "Float.hpp"
#include "String.hpp"
#include "Bool.hpp"
#include "Vector.hpp"
#include "Table.hpp"
#include "Reference.hpp"
#include <ctype.h>

namespace Lizzy
{
	class Integer : public Data
	{
	private:
		long value;
	public:
		Integer(long value=0L);
		Integer(string expr);
		Integer(const Integer& cp);
		Integer(Data *data);
		~Integer();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		long get() const;
		void set(long newValue);
		void set(Data *data) override;
		void set(string value) override;
		Integer& operator=(const Integer& cp);
	};
}


#endif
