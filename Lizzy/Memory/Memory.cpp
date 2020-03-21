#include "Memory.hpp"


const string Memory::VECTOR_ID = "\1";
const string Memory::VECTOR_ELEM_SEP_ID = "\2";


Memory::Memory() : map<string, Generic *>()
{
	cout << "Memory created" << endl;
}

Memory::~Memory()
{
	for(auto it : *this)
	{
		if(it.second->getHashType() == typeid(vector<Generic *>).hash_code())
		{
			for(auto *gen : it.second->ref<vector<Generic *>>())
			{
				delete gen;
			}
		}
		delete it.second;
	}
	cout << "Memory deleted" << endl;
}

bool Memory::exists(string id)
{
	return find(id) != end();
}

void Memory::addMemory(string id, string strGenValue)
{
	if(not exists(id))
	{
		Generic *var = new Generic(0);
		modifyGeneric(var, strGenValue);
		(*this)[id] = var;
	}
	else
	{
		throw Exception(id + " Memory already exists");
	}
}

void Memory::setMemory(string id, string strGenValue)
{
	if(exists(id))
	{
		modifyGeneric((*this)[id], strGenValue);
	}
	else
	{
		throw Exception(id +  " Memory not exists");
	}
}

vector<Generic *> Memory::createVector(string vecs)
{
	vector<Generic *> vec;
	if(vecs.size() == 0) return vec;
	vecs = vecs.substr(1);cout << "Vector created " << vecs << endl;
	/*
	fractionner la string afin qu'elle ne découpe pas les deux vecteurs à la fois
	*/
	for(auto s : String(vecs).split(VECTOR_ELEM_SEP_ID))
	{

		Generic *gen = new Generic(0);
		modifyGeneric(gen, s);
		vec.push_back(gen);
	}
	return vec;
}

void Memory::modifyGeneric(Generic *gen, string strGenValue)
{
	switch(type(strGenValue))
	{
		case INTEGER_T:
			*gen = (long)atol(strGenValue.c_str());
			break;
		case FLOAT_T:
			*gen = (double)atof(strGenValue.c_str());
			break;
		case VECTOR_T:
			*gen = Memory::createVector(strGenValue);
			break;
		case OBJECT_T:
			break;
		case BOOL_T:
			*gen = (bool)(strGenValue == "true");
			break;
		default:
			*gen = (string)strGenValue;
	}
}

Generic& Memory::getMemory(string id)
{
	if(exists(id)) return *(*this)[id];
	throw Exception(id + " Memory does not exists");
}

MemType Memory::type(string constStrGenValue)
{
	if(isInteger(constStrGenValue)) return INTEGER_T;
	if(isFloat(constStrGenValue)) return FLOAT_T;
	if(isVector(constStrGenValue)) return VECTOR_T;
	if(isObject(constStrGenValue)) return OBJECT_T;
	if(isBool(constStrGenValue)) return BOOL_T;
	return STRING_T;
}

string Memory::constType(string constStrGenValue)
{
	if(isInteger(constStrGenValue)) return "Integer";
	if(isFloat(constStrGenValue)) return "Float";
	if(isVector(constStrGenValue)) return "Vector";
	if(isObject(constStrGenValue)) return "Object";
	if(isBool(constStrGenValue)) return "Bool";
	return "String";
}

bool Memory::isInteger(string v)
{
	auto len = v.size();
	for(int i = 0; i < len; i++)
	{
		if(not i and v[i] == '-') continue;
		if(not isdigit(v[i])) return false;
	}
	return true;
}

bool Memory::isFloat(string v)
{
	auto len = v.size();
	int ptCounter = 0;
	for(int i = 0; i < len; i++)
	{
		if(not i and v[i] == '-') continue;
		if(not isdigit(v[i]))
		{
			if(i != 0 and i != len -1 and ptCounter == 0 and v[i] == '.')
			{
				ptCounter++;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool Memory::isVector(string v)
{
	return v.size() and v[0] == VECTOR_ID[0];
}

bool Memory::isObject(string v)
{
	return false;
}

bool Memory::isBool(string v)
{
	return v == "true" or v == "false";
}

string Memory::vectorToString(vector<Generic *>& vec, bool keepvecID)
{
	string buf;
	string sep = " ";
	if(keepvecID)
	{
		sep = VECTOR_ELEM_SEP_ID;
		buf = VECTOR_ID;
	}
	for(auto *gen : vec)
	{
		buf += Memory::toString(*gen, keepvecID) + sep;
	}
	if(buf.size()) buf.pop_back();
	return buf;
}

string Memory::getVectorElement(string id, int index)
{
	Generic& gen = getMemory(id);
	if(gen.getHashType() == typeid(vector<Generic *>).hash_code())
	{
		if(gen.ref<vector<Generic *>>().size() <= index) throw Exception(to_string(index) + " is out of band of the Vector " + id);
		return toString(*gen.ref<vector<Generic *>>()[index], false);
	}
	throw Exception(id + " not a vector");
}

string Memory::toString(Generic &gen, bool keepvecID)
{
	auto hash = gen.getHashType();
	if(hash == typeid(double).hash_code()) return to_string(gen.ref<double>());
	if(hash == typeid(long).hash_code()) return to_string(gen.ref<long>());
	if(hash == typeid(vector<Generic *>).hash_code()) return vectorToString(gen.ref<vector<Generic *>>(), keepvecID);
	if(hash == typeid(bool).hash_code()) return gen.ref<bool>() ? "true" : "false";
	return gen.ref<string>();
}

string Memory::toString(string id, bool keepvecID)
{
	return toString(getMemory(id), keepvecID);
}

string Memory::getType(string id)
{
	Generic &gen = getMemory(id);
	auto hash = gen.getHashType();
	if(hash == typeid(double).hash_code()) return "Float";
	if(hash == typeid(long).hash_code()) return "Integer";
	if(hash == typeid(vector<Generic *>).hash_code()) return "Vector";
	//Object
	if(hash == typeid(bool).hash_code()) return "Bool";
	return "String";
}
