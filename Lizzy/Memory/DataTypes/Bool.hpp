#ifndef LIZZY_BOOL_HPP
#define LIZZY_BOOL_HPP
#include "Data.hpp"

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
		~Bool();
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		bool get() const;
		void set(bool newValue);
		Bool& operator=(const Bool& cp);
	};
}


#endif
