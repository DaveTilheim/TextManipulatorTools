#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <iostream>
#include <string>

using namespace std;

class Exception
{
protected:
	const string message;
public:
	Exception();
	Exception(string message);
	Exception(const Exception& other);
	virtual ~Exception();
	Exception& operator=(const Exception& other) = delete;
	string what() const;
	string getMessage() const;
};

#endif
