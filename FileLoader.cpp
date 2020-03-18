#include "FileLoader.hpp"



FileLoader::FileLoader(string filename)
{
	update(filename);
}

FileLoader::FileLoader() : index(0)
{
	
}

void FileLoader::update(string filename, bool flush)
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

void FileLoader::drop()
{
	content.erase(content.begin() + index);

}

string FileLoader::getCurrentFile() const
{
	return currentFile;
}

String& FileLoader::getLine(int i)
{
	if(i == -1) return content[getIndex()];
	return content[i];
}

int FileLoader::getIndex() const
{
	return index;
}

void FileLoader::setIndex(int i)
{
	if(i < 0) i = -1;
	else if(i > content.size()) i = content.size();
	index = i;
}

void FileLoader::next()
{
	setIndex(getIndex() + 1);
}

void FileLoader::prec()
{
	setIndex(getIndex() - 1);
}

bool FileLoader::end() const
{
	return getIndex() >= content.size();
}

void FileLoader::insert(FileLoader& other)
{
	other.foreach([this](String& line)
	{
		content.insert(content.begin() + getIndex(), line);
		next();
	});
}

void FileLoader::foreach(function<void(String&)> action)
{
	setIndex(0);
	while(not end())
	{
		action(getLine());
		next();
	}
	setIndex(0);
}

int FileLoader::size() const
{
	return content.size();
}

ostream& operator<<(ostream& out, const FileLoader& fr)
{
	int line = 1;
	for(auto s : fr.content)
	{
		out << line++ << ": " << s << endl;
	}
	return out;
}
