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

size_t Generic::type() const
{
	return typeHash;
}

Generic Generic::operator+(const Generic& g1)
{
	return Generic::types[typeHash].add_operator(data, g1.data);
}

Generic Generic::operator-(const Generic& g1)
{
	return Generic::types[typeHash].sub_operator(data, g1.data);
}

Generic Generic::operator*(const Generic& g1)
{
	return Generic::types[typeHash].mul_operator(data, g1.data);
}

Generic Generic::operator/(const Generic& g1)
{
	return Generic::types[typeHash].div_operator(data, g1.data);
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
	return Generic::types[value.typeHash].print(out, value.data);
}

istream& operator>>(istream& in, const Generic& value)
{
	return Generic::types[value.typeHash].input(in, value.data);
}
