#ifndef LIZZY_STRING_HPP
#define LIZZY_STRING_HPP
#include "Data.hpp"

namespace Lizzy
{
	class String : public Data
	{
	private:
		string value;
	public:
		String(string value="");
		String(const String& cp);
		~String();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		string get() const;
		void set(string newValue);
		String& operator=(const String& cp);
		char& operator[](int i);
	};
}


#endif
