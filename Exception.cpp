#include "Exception.hpp"


Exception::Exception() : message("an exception has occured")
{

}

Exception::Exception(string message) : message(message)
{

}

Exception::Exception(const Exception& other) : message(other.getMessage())
{

}

Exception::~Exception()
{

}

string Exception::what() const
{
	return "###[ERROR]### " + getMessage() + " ###[ERROR]###";
}

string Exception::getMessage() const
{
	return message;
}
