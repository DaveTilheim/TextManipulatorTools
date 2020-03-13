#include "String.hpp"


String::String(const string& s) : string(s)
{

}

void String::replace(string olds, string news)
{
	int i = 0;
	size_t oldLen = olds.size();
	size_t newLen = news.size();
	while((i = find(olds, i)) != -1)
	{
		string::replace(i, oldLen, news);
		i += newLen;
	}
}

void String::remove(string chars)
{
	size_t len = chars.size();
	for(int i = 0; i < len; i++)
	{
		string s(1, chars[i]);
		replace(s);
	}
}

vector<String> String::split(string sep, bool keepsep) const
{
	vector<String> tmp;
	int i = 0;
	int bef = 0;
	size_t sepLen = sep.size();
	while((i = find(sep, i)) != -1)
	{
		if(substr(bef, i - bef).size())
		{
			tmp.push_back(substr(bef, i - bef));
		}
		if(keepsep)
			tmp.push_back(String(sep));
		bef = i + sepLen;
		i += sepLen;
	}
	if(size())
	{
		if(substr(bef).size())
		{
			tmp.push_back(substr(bef));
		}
	}
	return tmp;
}

vector<string> String::split_std(string sep, bool keepsep) const
{
	vector<string> tmp;
	auto splited = split(sep, keepsep);
	for(auto s : splited)
	{
		tmp.push_back(s);
	}
	return tmp;
}

int String::toInt() const
{
	return atoi(c_str());
}

double String::toDouble() const
{
	return atof(c_str());
}

String::operator int() const
{
	return toInt();
}

String::operator double() const
{
	return toDouble();
}


