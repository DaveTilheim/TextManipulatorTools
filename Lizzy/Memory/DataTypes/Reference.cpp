#include "Reference.hpp"


using namespace Lizzy;



Reference::Reference(Data **value) : value(value)
{

}

Reference::Reference(string expr) : value(reinterpret_cast<Data **>(atoi(expr.c_str())))
{

}

Reference::Reference(const Reference& cp) : value(cp.value)
{

}

Reference::~Reference()
{
	value = nullptr;
}

int Reference::getAttr()
{
	if(value and *value) return (*value)->getAttr();
	return attr;
}

void Reference::setAttr(int attr)
{
	if(value and *value) (*value)->setAttr(attr);
	Data::setAttr(attr);
}

void Reference::setRefAttr(int attr)
{
	Data::setAttr(attr);
}

int Reference::getRefAttr() const
{
	return attr;
}

string Reference::toString()
{
	if(value and *value) return (*value)->toString();
	return "null";
}

string Reference::type()
{
	if(value and *value) return (*value)->type();
	return "Reference";
}

Types Reference::typeId()
{
	if(value and *value) return (*value)->typeId();
	return REFERENCE_T;
}

Data *Reference::dup()
{
	if(value and *value) return (*value)->dup();
	return new Reference(nullptr);
}

Data *Reference::get() const
{
	return value ? *value : nullptr;
}

Data **Reference::getRef() const
{
	return value;
}

void Reference::set(Data **newValue)
{
	value = newValue;
}

Reference& Reference::operator=(const Reference& cp)
{
	value = cp.value;
	return *this;
}

bool Reference::is(string expr)
{
	return false;
}