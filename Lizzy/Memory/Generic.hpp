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
	template <class U> static char test_print_lambdacout(decltype(std::cout << std::declval<const U&>()));
	template <class U> static long test_print_lambdacout(...);
	template <class U> static char test_add_operator(decltype(&U::operator+));
	template <class U> static long test_add_operator(...);
	template <class U> static char test_sub_operator(decltype(&U::operator-));
	template <class U> static long test_sub_operator(...);
	enum
	{
		printable = sizeof(test_print_lambdacout<T>(cout)) == sizeof(char),
		has_add_operator = sizeof(test_add_operator<T>(0)) == sizeof(char),
		has_sub_operator = sizeof(test_sub_operator<T>(0)) == sizeof(char)
	};

	template <class U> static function<ostream&(ostream&, void *)> print_lambda(decltype(std::cout << std::declval<const U&>()))
	{
		return [](ostream& out, void *data) -> ostream&
		{
			return out << *(U *)data;
		};
	}
	template <class U> static function<ostream&(ostream&, void *)> print_lambda(const ostream&)
	{
		return [](ostream& out, void *data) -> ostream&
		{
			return out << "<no print function>";
		};
	}
	static function<ostream&(ostream&, void *)> print()
	{
		return print_lambda<T>(cout);
	}
};

struct Type
{
	function<void(void *)> destructor;
	function<void *(void *)> copy;
	function<ostream& (ostream&, void *)> print;
	Type(){}
	~Type(){}
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

	size_t getHashType() const { return typeHash; }

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
			Type type;
			type.destructor = [](void *data)
			{
				if(data)
				{
					delete (T *)data;
				}
			};
			type.copy = [](void *data)
			{
				return new T(*(T *)data);
			};
			type.print = GenericMethod<T>::print();
			Generic::types[hash] = type;
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
