#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <vector>
#include "../../Exception.hpp"
#include "Generic.hpp"
#include <ctype.h>
#include "../../String.hpp"

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
private:
	static vector<Generic *> createVector(string vecs);
	static string vectorToString(vector<Generic *>&, bool keepvecID);
public:
	static const string VECTOR_ID;
	static const string VECTOR_ELEM_SEP_ID;
	Memory();
	~Memory();
	bool exists(string id);
	void addMemory(string id, string strGenValue);
	void setMemory(string id, string strGenValue);
	Generic& getMemory(string id);
	string toString(string id, bool keepvecID=false);
	static string toString(Generic &, bool keepvecID);
	string getType(string id);
	string getVectorElement(string id, int index);
	static MemType type(string constStrGenValue);
	static string constType(string constStrGenValue);
	static void modifyGeneric(Generic *gen, string strGenValue);
	static bool isInteger(string v);
	static bool isFloat(string v);
	static bool isVector(string v);
	static bool isObject(string v);
	static bool isBool(string v);
};


#endif
