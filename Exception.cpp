#include "Exception.hpp"


Exception::Exception() : message("an exception has occured")
{

}

Exception::Exception(string message) : message(message)
{

}

Exception::Exception(const Exception& other) : message(other.what())
{

}

Exception::~Exception()
{

}

string Exception::what() const
{
	return "### " + getMessage() + " ###";
}

string Exception::getMessage() const
{
	return message;
}
