#include "Generic.hpp"


map<size_t, Type> Generic::types = map<size_t, Type>();

Generic::Generic(const Generic& other)
{
	typeHash = other.typeHash;
	data = Generic::types[typeHash].copy(other.data);
}

Generic::Generic(const char *str) : Generic(string(str))
{

}

Generic::~Generic()
{
	Generic::types[typeHash].destructor(data);
}

string& Generic::operator=(const char *str)
{
	return operator=<string>(string(str));
}

Generic& Generic::operator=(const Generic& other)
{
	Generic::types[typeHash].destructor(data);
	typeHash = other.typeHash;
	data = Generic::types[typeHash].copy(other.data);
	return *this;
}

ostream& operator<<(ostream& out, const Generic& value)
{
	return out << value.typeHash;
}
