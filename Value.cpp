#include "Value.hpp"


map<size_t, Type> Value::types = map<size_t, Type>();

Value::Value(const Value& other)
{
	typeHash = other.typeHash;
	data = Value::types[typeHash].copy(other.data);
}

Value::Value(const char *str) : Value(string(str))
{

}

Value::~Value()
{
	Value::types[typeHash].destructor(data);
}

string& Value::operator=(const char *str)
{
	return operator=<string>(string(str));
}

Value& Value::operator=(const Value& other)
{
	Value::types[typeHash].destructor(data);
	typeHash = other.typeHash;
	data = Value::types[typeHash].copy(other.data);
	return *this;
}

ostream& operator<<(ostream& out, const Value& value)
{
	return out << value.typeHash;
}
