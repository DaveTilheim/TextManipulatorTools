#include "FileReader.hpp"



FileReader::FileReader(string filename)
{
	update(filename);
}

FileReader::FileReader() : index(0)
{
	
}

void FileReader::update(string filename, bool flush)
{
	if(flush) content.clear();
	setIndex(0);
	ifstream file(filename);
	if(file)
	{
		currentFile = filename;
		String buf;
		while(getline(file, buf))
		{
			buf.remove();
			if(buf.size())
			{
				content.push_back(buf);
			}
		}
		file.close();
	}
	else
	{
		throw Exception("'" + filename + "' file does not exists");
	}
}

void FileReader::drop()
{
	content.erase(content.begin() + index);

}

string FileReader::getCurrentFile() const
{
	return currentFile;
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

void FileReader::insert(FileReader& other)
{
	other.foreach([this](String& line)
	{
		content.insert(content.begin() + getIndex(), line);
		next();
	});
}

void FileReader::foreach(function<void(String&)> action)
{
	setIndex(0);
	while(not end())
	{
		action(getLine());
		next();
	}
	setIndex(0);
}

int FileReader::size() const
{
	return content.size();
}

ostream& operator<<(ostream& out, const FileReader& fr)
{
	int line = 1;
	for(auto s : fr.content)
	{
		out << line++ << ": " << s << endl;
	}
	return out;
}
