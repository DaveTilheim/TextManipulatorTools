#ifndef LIZZY_BOOL_HPP
#define LIZZY_BOOL_HPP
#include "Float.hpp"
#include "String.hpp"
#include "Integer.hpp"
#include "Vector.hpp"
#include "Table.hpp"
#include "Reference.hpp"

namespace Lizzy
{
	class Bool : public Data
	{
	private:
		bool value;
	public:
		Bool(bool value=false);
		Bool(string expr);
		Bool(const Bool& cp);
		Bool(Data *data);
		~Bool();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		bool get() const;
		void set(bool newValue);
		void setFromData(Data *data);
		void setFromValue(string value);
		Bool& operator=(const Bool& cp);
	};
}


#endif
