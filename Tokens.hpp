#ifndef TOKENS_HPP
#define TOKENS_HPP
#include "String.hpp"
#include <functional>
#include <fstream>

class Tokens : public vector<String>
{
private:
	bool keepSeparator;
	int index;
	string separator;
public:
	Tokens();
	Tokens(const String& str, const string& sep=" ", bool keep=false);
	Tokens(const string& str, const string& sep=" ", bool keep=false);
	Tokens(const Tokens& other);
	Tokens(const vector<String>& vec, const string& sep=" ", bool keep=false);
	void setTokens(const String& str);
	void setIndex(int i);
	void setSeparator(string sep);
	void setKeepSeparator(bool state);
	int getIndex() const;
	string getSeparator() const;
	bool getKeepSeparator() const;
	String getString() const;
	String getCurrent() const;
	void next();
	void prec();
	bool oob() const;
	void resetIndex();
	void foreach(function<void(String& token)> operation);
	Tokens partial() const;
	int partialSize() const;
	bool read(istream& in, char del='\n');
	void clean();
	Tokens& operator=(const Tokens& other);
	operator string();
	operator String();
	operator int();
	operator double();
	friend ostream& operator<<(ostream& out, const Tokens& tokens);
};

#endif
