#ifndef VALUE_HPP
#define VALUE_HPP
#include <functional>
#include <map>
#include <typeinfo>
#include <string>
#include <iostream>

using namespace std;

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

class Value
{
private:
	void *data = nullptr;
	size_t typeHash = 0;
	static map<size_t, Type> types;
public:

	template <class T> Value(const T& value)
	{
		Value::configureType<T>();
		typeHash = typeid(T).hash_code();
		data = new T(value);
	}

	Value(const Value& other);
	Value(const char *str);
	~Value();

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
		if(Value::types.find(hash) == Value::types.end())
		{
			Value::types[hash] = Type(
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
			Value::types[typeHash].destructor(data);
			Value::configureType<T>();
			typeHash = typeid(T).hash_code();
			data = new T(value);
		}
		return *(T *)data;
	}

	string& operator=(const char *str);
	Value& operator=(const Value& other);
	friend ostream& operator<<(ostream& out, const Value& value);
};

#endif
