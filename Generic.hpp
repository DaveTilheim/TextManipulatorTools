#ifndef GENERIC_HPP
#define GENERIC_HPP
#include <functional>
#include <map>
#include <typeinfo>
#include <string>
#include <iostream>

using namespace std;

class Generic;

template <class T> class GenericMethod
{
public:
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
			return out << typeid(U).name() <<":"<<data;
		};
	}

	static function<ostream&(ostream&, void *)> print()
	{
		return print_lambda<T>(cout);
	}


	template <class U> static function<istream&(istream&, void *)> input_lambda(decltype(std::cin >> std::declval<U&>()))
	{
		return [](istream& in, void *data) -> istream&
		{
			return in >> *(U *)data;
		};
	}
	template <class U> static function<istream&(istream&, void *)> input_lambda(const istream&)
	{
		return [](istream& in, void *data) -> istream&
		{
			return in;
		};
	}

	static function<istream&(istream&, void *)> input()
	{
		return input_lambda<T>(cin);
	}

	template <class U> static function<Generic(void *, void *)> add_operator_lambda(decltype(U() + U()))
	{
		return [](void *u1, void *u2)
		{
			return Generic(*(U *)u1 + *(U *)u2);
		};
	}

	template <class U> static function<Generic(void *, void *)> add_operator_lambda(U)
	{
		return [](void *, void *)
		{
			return Generic(U());
		};
	}

	static function<Generic(void *, void *)> add_operator()
	{
		return add_operator_lambda<T>(T());
	}


	template <class U> static function<Generic(void *, void *)> sub_operator_lambda(decltype(U() - U()))
	{
		return [](void *u1, void *u2)
		{
			return Generic(*(U *)u1 - *(U *)u2);
		};
	}

	template <class U> static function<Generic(void *, void *)> sub_operator_lambda(U)
	{
		return [](void *, void *)
		{
			return Generic(U());
		};
	}

	static function<Generic(void *, void *)> sub_operator()
	{
		return sub_operator_lambda<T>(T());
	}

	template <class U> static function<Generic(void *, void *)> mul_operator_lambda(decltype(U() * U()))
	{
		return [](void *u1, void *u2)
		{
			return Generic(*(U *)u1 * *(U *)u2);
		};
	}

	template <class U> static function<Generic(void *, void *)> mul_operator_lambda(U)
	{
		return [](void *, void *)
		{
			return Generic(U());
		};
	}

	static function<Generic(void *, void *)> mul_operator()
	{
		return mul_operator_lambda<T>(T());
	}


	template <class U> static function<Generic(void *, void *)> div_operator_lambda(decltype(U() / U()))
	{
		return [](void *u1, void *u2)
		{
			return Generic(*(U *)u1 / *(U *)u2);
		};
	}

	template <class U> static function<Generic(void *, void *)> div_operator_lambda(U)
	{
		return [](void *, void *)
		{
			return Generic(U());
		};
	}

	static function<Generic(void *, void *)> div_operator()
	{
		return div_operator_lambda<T>(T());
	}
};

struct Type
{
	function<void(void *)> destructor;
	function<void *(void *)> copy;
	function<ostream& (ostream&, void *)> print;
	function<istream& (istream&, void *)> input;
	function<Generic (void *, void *)> add_operator;
	function<Generic (void *, void *)> sub_operator;
	function<Generic (void *, void *)> mul_operator;
	function<Generic (void *, void *)> div_operator;
	Type(){}
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
			type.input = GenericMethod<T>::input();
			type.add_operator = GenericMethod<T>::add_operator();
			type.sub_operator = GenericMethod<T>::sub_operator();
			type.mul_operator = GenericMethod<T>::mul_operator();
			type.div_operator = GenericMethod<T>::div_operator();
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

	size_t type() const;
	string& operator=(const char *str);
	Generic& operator=(const Generic& other);
	Generic operator+(const Generic&);
	Generic operator-(const Generic&);
	Generic operator*(const Generic&);
	Generic operator/(const Generic&);
	friend ostream& operator<<(ostream& out, const Generic& value);
	friend istream& operator>>(istream& in, const Generic& value);
};

#endif
