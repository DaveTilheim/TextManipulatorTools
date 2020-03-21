#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class LizzyInteger;
class LizzyFloat;
class LizzyBool;
class LizzyString;
class LizzyVector;
class LizzyObject;
class LizzyClass;
class LizzyTable;


class LizzyDataAttr
{
private:
	bool _const : 1 = false;
	bool _persistant : 1 = false;
public:
	bool isConst() const
	{
		return _const;
	}
	void enableConst()
	{
		_const = true;
	}
	void disableConst()
	{
		_const = false;
	}
	bool isPersistant() const
	{
		return _persistant;
	}
	void enablePersistant()
	{
		_persistant = true;
	}
	void disablePersistant()
	{
		_persistant = false;
	}
};

class LizzyData
{
private:
	LizzyDataAttr attr;
public:
	virtual ~LizzyData()
	{
		
	}
	virtual string toString() = 0;

	LizzyDataAttr& getAttr()
	{
		return attr;
	}
	template <class LD> bool is()
	{
		return dynamic_cast<LD *>(this);
	}
	string type()
	{
		if(is<LizzyInteger>()) return "Integer";
		if(is<LizzyFloat>()) return "Float";
		if(is<LizzyBool>()) return "Bool";
		if(is<LizzyString>()) return "String";
		if(is<LizzyVector>()) return "Vector";
		if(is<LizzyObject>()) return "Object";
		if(is<LizzyClass>()) return "Class";
		if(is<LizzyTable>()) return "Table";
		return "undefined";
	}

	virtual LizzyData *dup()
	{
		return nullptr;
	}
};


class LizzyInteger : public LizzyData
{
private:
	long value;
public:
	LizzyInteger(string expr)
	{
		value = atoi(expr.c_str());
	}

	LizzyInteger(const LizzyInteger& cp)
	{
		value = cp.value;
	}

	~LizzyInteger()
	{
		cout << "delete " << type() << endl;
	}

	string toString() override
	{
		return to_string(value);
	}

	long get() { return value; }

	LizzyData *dup() override
	{
		return new LizzyInteger(*dynamic_cast<LizzyInteger *>(this));
	}
};


class LizzyBool : public LizzyData
{
private:
	bool value;
public:
	LizzyBool(string expr)
	{
		value = expr == "true";
	}

	LizzyBool(const LizzyBool& cp)
	{
		value = cp.value;
	}

	~LizzyBool()
	{
		cout << "delete " << type() << endl;
	}

	string toString() override
	{
		return value ? "true" : "false";
	}

	bool get() { return value; }

	LizzyData *dup() override
	{
		return new LizzyBool(*dynamic_cast<LizzyBool *>(this));
	}
};

class LizzyFloat : public LizzyData
{
private:
	double value;
public:
	LizzyFloat(string expr)
	{
		value = atof(expr.c_str());
	}

	LizzyFloat(const LizzyFloat& cp)
	{
		value = cp.value;
	}

	~LizzyFloat()
	{
		cout << "delete " << type() << endl;
	}

	string toString() override
	{
		return to_string(value);
	}

	long get() { return value; }

	LizzyData *dup() override
	{
		return new LizzyFloat(*dynamic_cast<LizzyFloat *>(this));
	}
};

class LizzyString : public LizzyData
{
private:
	string value;
public:
	LizzyString(string expr)
	{
		value = expr;
	}

	LizzyString(const LizzyString& cp)
	{
		value = cp.value;
	}

	~LizzyString()
	{
		cout << "delete " << type() << endl;
	}

	string toString() override
	{
		return value;
	}

	string get() { return value; }

	LizzyData *dup() override
	{
		return new LizzyString(*dynamic_cast<LizzyString *>(this));
	}
};
#include <vector>
#include <map>
class LizzyVector : public LizzyData
{
private:
	vector<LizzyData *> value;
public:
	LizzyVector()
	{
		
	}

	LizzyVector(const LizzyVector& cp)
	{
		for(auto *ld : cp.value)
		{
			value.push_back(ld->dup());
		}
	}

	~LizzyVector()
	{
		for(auto *ld : value)
		{
			delete ld;
		}
		cout << "delete " << type() << endl;
	}

	void add(LizzyData *ld)
	{
		value.push_back(ld);
	}

	void foreach(void (*operation)(LizzyData *))
	{
		for(auto *ld : value)
		{
			operation(ld);
		}
	}

	string toString() override
	{
		string buf;
		for(auto *ld : value)
		{
			buf += ld->toString() + " ";
		}
		if(buf.size()) buf.pop_back();
		return buf;
	}

	vector<LizzyData *> get() { return value; }
	LizzyData * get(int i) { return value[i]; }

	LizzyData *dup() override
	{
		return new LizzyVector(*dynamic_cast<LizzyVector *>(this));
	}
};


class LizzyClassAttribute : public LizzyData
{
private:
	LizzyData *defaultValue;
public:
	LizzyClassAttribute(LizzyData *dv=nullptr) : defaultValue(dv)
	{

	}

	~LizzyClassAttribute()
	{
		if(defaultValue) delete defaultValue;
	}

	LizzyData *getDefault()
	{
		return defaultValue;
	}


	string toString() override
	{
		return "none";
	}
};


class LizzyClass : public LizzyData
{
private:
	map<string, LizzyClassAttribute *> attributes;
	vector<string> methods;
	bool lock = false;
public:
	LizzyClass()
	{

	}

	~LizzyClass()
	{
		for(auto it : attributes)
		{
			delete it.second;
		}
	}

	void addAttName(string name, LizzyData *defaultValue=nullptr)
	{
		if(not lock)
			attributes[name] = new LizzyClassAttribute(defaultValue);
	}

	void addMethod(string name)
	{
		if(not lock)
			methods.push_back(name);
	}

	string toString() override
	{
		return "none";
	}

	void lockClass()
	{
		lock = true;
	}

	const map<string, LizzyClassAttribute *>& getMemberAttr() const
	{
		return attributes;
	}
};

class LizzyObject : public LizzyData
{
private:
	map<string, LizzyData *> value;

	map<string, LizzyData *>& get() { return value; }
public:
	LizzyObject(LizzyClass& lclass)
	{
		for(auto it : lclass.getMemberAttr())
		{
			value[it.first] = it.second->getDefault() ? it.second->getDefault()->dup() : nullptr;
		}
	}
	LizzyObject(const LizzyObject& cp)
	{
		value = cp.value;
	}
	~LizzyObject()
	{
		for(auto it : value)
		{
			delete it.second;
		}
	}

	void set(string id, LizzyData *data=nullptr)
	{
		if(value[id])
			delete value[id];
		value[id] = data;
	}

	LizzyData *get(string id)
	{
		return value[id];
	}

	string toString() override
	{
		return "none";
	}

	LizzyData *dup() override
	{
		return new LizzyObject(*dynamic_cast<LizzyObject *>(this));
	}
};

class LizzyTable : public LizzyData
{
private:
	map<string, LizzyData *> value;
public:
	LizzyTable()
	{
		
	}

	~LizzyTable()
	{
		for(auto it : value)
		{
			delete it.second;
		}
		cout << "delete " << type() << endl;
	}

	string toString() override
	{
		return "none";
	}

	void add(string id, LizzyData *data=nullptr)
	{
		value[id] = data;
	}

	void set(string id, LizzyData *data=nullptr)
	{
		if(value[id])
			delete value[id];
		value[id] = data;
	}

	LizzyData *get(string id)
	{
		return value[id];
	}

	map<string, LizzyData *>& getTable() { return value; }
};

#define LizzyGet(type, pname, var) ((Lizzy##type *)var.get(#pname))->get()
int main(int argc, char const *argv[])
{
	LizzyClass cl;
	cl.addAttName("name", new LizzyString("Arthur"));
	cl.addAttName("age");
	cl.addAttName("school", new LizzyString("HEPL"));
	cl.lockClass();
	
	LizzyObject lo(cl);
	lo.set("age", new LizzyInteger("666"));
	cout << ((LizzyString *)lo.get("name"))->get()<< " " << ((LizzyInteger *)lo.get("age"))->get()<<endl;
	cout << LizzyGet(String, school, lo) << endl;

	return 0;
}
