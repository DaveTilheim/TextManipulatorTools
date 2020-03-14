#ifndef STRING_HPP
#define STRING_HPP
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class String : public string
{
public:
	using string::string;
	String(const string& s);
	void replace(string olds, string news="");
	void remove(string chars="\n\t\a\t\v\e\r");
	vector<String> split(string sep=" ", bool keepsep=false) const;
	vector<string> split_std(string sep=" ", bool keepsep=false) const;
	vector<String> stepSplit(string sep1="(", string sep2=")", bool keepsep=false) const;
	vector<string> stepSplit_std(string sep1="(", string sep2=")", bool keepsep=false) const;
	int toInt() const;
	double toDouble() const;
	operator int() const;
	operator double() const;
};


#endif
