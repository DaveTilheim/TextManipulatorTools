#ifndef LIZZY_STRING_HPP
#define LIZZY_STRING_HPP
#include "Integer.hpp"
#include "Float.hpp"
#include "Bool.hpp"
#include "Vector.hpp"
#include "Table.hpp"
#include "Reference.hpp"

namespace Lizzy
{
	class String : public Data
	{
	private:
		string value;
	public:
		String(string value="");
		String(const String& cp);
		String(Data *data);
		~String();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		string get() const;
		void set(string newValue);
		void setFromValue(string value);
		void setFromData(Data *data);
		String& operator=(const String& cp);
		char& operator[](int i);
	};
}


#endif
