#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <vector>
#include "../../Exception.hpp"
#include "Generic.hpp"
#include <ctype.h>

using namespace std;


enum MemType
{
	INTEGER_T,
	FLOAT_T,
	BOOL_T,
	STRING_T,
	VECTOR_T,
	OBJECT_T
};


class Memory : private map<string, Generic *>
{
public:
	Memory();
	~Memory();
	bool exists(string id);
	void addMemory(string id, string strGenValue);
	void setMemory(string id, string strGenValue);
	Generic& getMemory(string id);
	string toString(string id);
	string getType(string id);
	static MemType type(string constStrGenValue);
	static string inferType(string constStrGenValue);
	static void modifyGeneric(Generic *gen, string strGenValue);
	static bool isInteger(string v);
	static bool isFloat(string v);
	static bool isVector(string v);
	static bool isObject(string v);
	static bool isBool(string v);
};


#endif
