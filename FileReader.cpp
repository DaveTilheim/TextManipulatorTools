#include "FileReader.hpp"



FileReader::FileReader(string filename)
{
	update(filename);
}

FileReader::FileReader() : index(0)
{
	
}

void FileReader::update(string filename)
{
	setIndex(0);
	ifstream file(filename);
	if(file)
	{
		string buf;
		while(getline(file, buf))
		{
			content.push_back(buf);
		}
		file.close();
	}
}

void FileReader::drop()
{
	content.erase(content.begin() + index);

}

String& FileReader::getLine(int i)
{
	if(i == -1) return content[getIndex()];
	return content[i];
}

int FileReader::getIndex() const
{
	return index;
}

void FileReader::setIndex(int i)
{
	if(i < 0) i = 0;
	else if(i > content.size()) i = content.size();
	index = i;
}

void FileReader::next()
{
	setIndex(getIndex() + 1);
}

void FileReader::prec()
{
	setIndex(getIndex() - 1);
}

bool FileReader::end() const
{
	return getIndex() >= content.size();
}
