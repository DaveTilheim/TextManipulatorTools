#ifndef FILE_READER_HPP
#define FILE_READER_HPP
#include <fstream>
#include "String.hpp"
#include <vector>

using namespace std;


class FileReader
{
private:
	vector<String> content;
	int index;
public:
	FileReader();
	FileReader(string filename);
	void update(string filename);
	String& getLine(int i=-1);
	int getIndex() const;
	void setIndex(int i);
	void drop();
	void next();
	void prec();
	bool end() const;
};


#endif
