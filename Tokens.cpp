#include "Tokens.hpp"


Tokens::Tokens()
{
	setIndex(0);
	setSeparator(" ");
	setKeepSeparator(false);
}


Tokens::Tokens(const String& str, const string& sep, bool keep)
{
	setIndex(0);
	setSeparator(sep);
	setKeepSeparator(keep);
	setTokens(str);
}

Tokens::Tokens(const Tokens& other) : vector<String>(other)
{
	setIndex(other.getIndex());
	setSeparator(other.getSeparator());
	setKeepSeparator(other.getKeepSeparator());
}

Tokens::Tokens(const vector<String>& vec, const string& sep, bool keep) : vector<String>(vec)
{
	setIndex(0);
	setSeparator(sep);
	setKeepSeparator(keep);
}

void Tokens::setTokens(const String& str)
{
	if(str.size())
	{
		*this = str.split(getSeparator(), getKeepSeparator());
	}
	else
	{
		clear();
	}
}

void Tokens::setIndex(int i)
{
	if(i <= size() and i >= -1)
		index = i;
}

bool Tokens::oob() const
{
	return getIndex() == size() or getIndex() == -1;
}

void Tokens::setSeparator(string sep)
{
	separator = sep;
}

void Tokens::setKeepSeparator(bool keep)
{
	keepSeparator = keep;
}

int Tokens::getIndex() const
{
	return index;
}

string Tokens::getSeparator() const
{
	return separator;
}

bool Tokens::getKeepSeparator() const
{
	return keepSeparator;
}

String Tokens::getString() const
{
	String buf;
	for(auto token : *this)
	{
		buf += token + " ";
	}
	if(buf.size())
	{
		buf.pop_back();
	}
	return buf;
}

String Tokens::getCurrent() const
{
	if(oob())
		return "";
	return (*this)[getIndex()];
}

void Tokens::next()
{
	setIndex(getIndex() + 1);
}

void Tokens::prec()
{
	setIndex(getIndex() - 1);
}

void Tokens::foreach(function<void(String& token)> operation)
{
	size_t len = size();
	for(int i = 0; i < len; i++)
	{
		operation((*this)[i]);
	}
}

void Tokens::resetIndex()
{
	setIndex(0);
}

Tokens Tokens::partial() const
{
	Tokens copy = *this;
	copy.erase(copy.begin() + 0, copy.begin() + copy.getIndex());
	return copy;
}

int Tokens::partialSize() const
{
	return size() - getIndex();
}

bool Tokens::read(istream& in, char del)
{
	string buf;
	if(getline(in, buf, del))
	{
		setTokens(buf);
		return true;
	}
	return false;
}

void Tokens::clean()
{
	size_t len = size();
	for(int i = 0; i < len; i++)
	{
		if((*this)[i].size() == 0)
		{
			erase(begin() + i, begin() + i + 1);
			len--;
		}
	}
}

Tokens& Tokens::operator=(const Tokens& other)
{
	setIndex(other.getIndex());
	setSeparator(other.getSeparator());
	setKeepSeparator(other.getKeepSeparator());
	vector<String>::operator=(other);
	return *this;
}

Tokens::operator string()
{
	string current = getCurrent();
	next();
	return current;
}

Tokens::operator String()
{
	String current = getCurrent();
	next();
	return current;
}

ostream& operator<<(ostream& out, const Tokens& tokens)
{
	string buf;
	for(auto token : tokens)
	{
		buf += token + tokens.getSeparator();
	}
	if(buf.size())
		buf.erase(buf.size() - tokens.getSeparator().size());
	return out << buf;
}


