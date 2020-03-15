#ifndef FILE_READER_HPP
#define FILE_READER_HPP
#include <fstream>
#include "String.hpp"
#include "Exception.hpp"
#include <vector>
#include <functional>

using namespace std;


class FileReader
{
private:
	vector<String> content;
	string currentFile;
	int index;
public:
	FileReader();
	FileReader(string filename);
	void update(string filename, bool flush=true);
	String& getLine(int i=-1);
	string getCurrentFile() const;
	int getIndex() const;
	void setIndex(int i);
	void drop();
	void next();
	void prec();
	bool end() const;
	void insert(FileReader& other);
	void foreach(function<void(String&)> action);
	int size() const;
	friend ostream& operator<<(ostream& out, const FileReader& fr);
};


#endif
