#ifndef LIZZY_REFERENCE_HPP
#define LIZZY_REFERENCE_HPP
#include "Data.hpp"
#include <ctype.h>

namespace Lizzy
{
	class Reference : public Data
	{
	private:
		Data **value;
	public:
		Reference(Data **ref=nullptr);
		Reference(string expr);
		Reference(const Reference& cp);
		~Reference();
		int getAttr() override;
		int getRefAttr() const;
		string toString() override;
		string type() override;
		Types typeId() override;
		Data *dup() override;
		static bool is(string expr);
		Data *get() const;
		Data **getRef() const;
		void set(Data **newValue);
		Reference& operator=(const Reference& cp);
	};
}


#endif
