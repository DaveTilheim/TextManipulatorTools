#ifndef FILE_READER_HPP
#define FILE_READER_HPP
#include <fstream>
#include "String.hpp"
#include "Exception.hpp"
#include <vector>
#include <functional>

using namespace std;
using namespace cmd;

class FileLoader
{
private:
	vector<String> content;
	string currentFile;
	int index;
public:
	FileLoader();
	FileLoader(string filename);
	void update(string filename, bool flush=true);
	String& getLine(int i=-1);
	string getCurrentFile() const;
	void separate(string sep);
	void keepsep(string sep);
	String getAll();
	int getIndex() const;
	void setIndex(int i);
	void drop();
	void next();
	void prec();
	bool end() const;
	void insert(FileLoader& other, int i=-1);
	void foreach(function<void(String&)> action);
	int size() const;
	friend ostream& operator<<(ostream& out, const FileLoader& fr);
};


#endif
