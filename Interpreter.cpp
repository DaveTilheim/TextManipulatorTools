#include "Interpreter.hpp"


FileReader *Interpreter::mainFileReader = nullptr;

Interpreter::Interpreter() : fileReader()
{
	if(not Interpreter::mainFileReader)
	{
		Interpreter::mainFileReader = &fileReader;
	}
	
	Action linkAction([this](Args args) -> string
	{
		string filename = args("file");
		if(alreadyLinked(filename))
		{
			fileReader.drop();fileReader.prec();
			return "";
		}
		FileReader fr(filename);
		linkedFiles.push_back(filename);
		fileReader.drop();
		int i = fileReader.getIndex() - 1;
		fileReader.insert(fr);
		fileReader.setIndex(i);
		return filename;
	});
	linkAction.setNamed("file");
	preIntCommand("link").setAction(1, linkAction);
}

Interpreter::~Interpreter()
{
	for(auto c : preIntCommands)
	{
		delete c.second;
	}
	Command::eraseCommandsWithPrefix(to_string((long)this));
}

void Interpreter::removeCommentary()
{
	fileReader.foreach([this](String& line)
	{
		int i;
		for(auto comSymbol : commentarySymbols)
		{
			if((i = line.find(comSymbol)) != string::npos)
			{
				line.erase(i);
			}
		}
	});
}

bool Interpreter::isPreInt(string str)
{
	return preIntCommands.find(str) != preIntCommands.end();
}

bool Interpreter::alreadyLinked(string filename) const
{
	for(string f : linkedFiles)
	{
		if(f == filename) return true;
	}
	return false;
}

void Interpreter::preIntCommandsRun()
{
	fileReader.foreach([this](String& line)
	{
		Tokens tok = line;
		String cname = tok;
		if(isPreInt(cname))
		{
			preIntCommands[cname]->run(tok);
		}
	});
}

void Interpreter::setAttributedCommandTag()
{
	fileReader.foreach([this](String& line)
	{
		line.replace("@", to_string((long)this));
	});
}

void Interpreter::preinterpretation()
{
	preIntCommandsRun();
	removeCommentary();
	setAttributedCommandTag();
}



vector<string> Interpreter::launch(string expr)
{
	Tokens exprTok = expr;
	vector<string> ret;
	while(not exprTok.oob())
	{
		String commandName = exprTok;
		Attributes attributes = Command::extractAttributes(commandName);
		if(not Command::isCommand(commandName))
			throw Exception("'" + commandName + "' is not a recognised Command");
		ret.push_back(Command::getCommand(commandName).run(exprTok, attributes.nargs));
	}
	return ret;
}


vector<string>  Interpreter::launchFile(string filename)
{
	vector<string> results;
	fileReader.update(filename);
	linkedFiles.push_back(filename);
	try
	{
		preinterpretation();
		while(not fileReader.end())
		{
			String line = fileReader.getLine();
			for(auto res : Interpreter::launch(line))
			{
				results.push_back(res);
			}
			fileReader.next();
		}
	}
	catch(const Exception& e)
	{
		cout << e.what() << endl;
	}
	linkedFiles.clear();
	return results;
}

FileReader& Interpreter::getFileReader()
{
	return fileReader;
}

FileReader& Interpreter::getMainFileReader()
{
	return *Interpreter::mainFileReader;
}

void Interpreter::setCommentarySymbol(string symbol)
{
	commentarySymbols.push_back(symbol);
}

Command& Interpreter::preIntCommand(string name)
{
	if(isPreInt(name)) return *preIntCommands[name];
	IndependantCommand *c = new IndependantCommand(name);
	preIntCommands[name] = c;
	return *c;
}

Command& Interpreter::attributedCommand(string name) const
{
	string cid = to_string((long)this) + name;
	if(Command::isCommand(cid))
	{
		return Command::getCommand(cid);
	}
	return *new Command(cid);
}

