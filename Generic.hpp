#ifndef GENERIC_HPP
#define GENERIC_HPP
#include <functional>
#include <map>
#include <typeinfo>
#include <string>
#include <iostream>

using namespace std;


template <class T> class GenericMethod
{
public:
	template <class U> static char test_add_operator(decltype(&U::operator+));
	template <class U> static long test_add_operator(...);
	template <class U> static char test_sub_operator(decltype(&U::operator-));
	template <class U> static long test_sub_operator(...);
	enum
	{
		has_add_operator = sizeof(test_add_operator<T>(0)) == sizeof(char),
		has_sub_operator = sizeof(test_sub_operator<T>(0)) == sizeof(char)
	};
};

struct Type
{
	function<void(void *)> destructor;
	function<void *(void *)> copy;
	Type(){}
	Type(function<void(void *)> destructor,
		 function<void *(void *)> copy)
	: destructor(destructor), copy(copy)
	{

	}
};

class Generic
{
private:
	void *data = nullptr;
	size_t typeHash = 0;
	static map<size_t, Type> types;
public:

	template <class T> Generic(const T& value)
	{
		Generic::configureType<T>();
		typeHash = typeid(T).hash_code();
		data = new T(value);
	}

	Generic(const Generic& other);
	Generic(const char *str);
	~Generic();

	template <class T> operator T&()
	{
		return *(T *)data;
	}

	template<class T> T copy()
	{
		return *(T *)data;
	}

	template<class T> T& ref()
	{
		return *(T *)data;
	}

	template <class T> static void configureType()
	{
		size_t hash = typeid(T).hash_code();
		if(Generic::types.find(hash) == Generic::types.end())
		{
			Generic::types[hash] = Type(
			[](void *data)
			{
				if(data)
				{
					delete (T *)data;
				}
			},
			[](void *data)
			{
				return new T(*(T *)data);
			});
		}
	}


	template <class T> T& operator=(const T& value)
	{
		if(typeid(T).hash_code() == typeHash)
		{
			ref<T>() = value;
		}
		else
		{
			Generic::types[typeHash].destructor(data);
			Generic::configureType<T>();
			typeHash = typeid(T).hash_code();
			data = new T(value);
		}
		return *(T *)data;
	}

	string& operator=(const char *str);
	Generic& operator=(const Generic& other);
	friend ostream& operator<<(ostream& out, const Generic& value);
};

#endif
