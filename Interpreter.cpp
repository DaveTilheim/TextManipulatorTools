#include "Interpreter.hpp"


FileLoader *Interpreter::mainFileLoader = nullptr;

Interpreter::Interpreter() : fileLoader()
{
	if(not Interpreter::mainFileLoader)
	{
		Interpreter::mainFileLoader = &fileLoader;
	}
	
	Action linkAction([this](Args args) -> string
	{
		string filename = args("file");
		if(alreadyLinked(filename))
		{
			fileLoader.drop();fileLoader.prec();
			return "";
		}
		FileLoader fr(filename);
		linkedFiles.push_back(filename);
		fileLoader.drop();
		int i = fileLoader.getIndex() - 1;
		fileLoader.insert(fr);
		fileLoader.setIndex(i);
		return filename;
	});
	linkAction.setNamed("file");
	preIntCommand("#link").setAction(1, linkAction);
}

Command& Interpreter::getLinker()
{
	return preIntCommand("#link");
}

void Interpreter::renamePreInt(string cmdname, string name)
{
	string old = cmdname;
	if(not isPreInt(name))
	{
		IndependantCommand *ic = preIntCommands[old];
		preIntCommands.erase(old);
		preIntCommands[name] = ic;
		preIntCommands[name]->rename(name);
	}
}
void Interpreter::removeAttributed()
{
	for(auto att : attributedCommands)
	{
		delete att;
	}
}

Interpreter::~Interpreter()
{
	for(auto c : preIntCommands)
	{
		delete c.second;
	}
	removeAttributed();
}

void Interpreter::removeCommentary()
{
	fileLoader.foreach([this](String& line)
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
	fileLoader.foreach([this](String& line)
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
	fileLoader.foreach([this](String& line)
	{
		line.replace("@", to_string(reinterpret_cast<uintptr_t>(this)));
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
	fileLoader.update(filename);
	linkedFiles.push_back(filename);
	preinterpretation();
	while(not fileLoader.end())
	{
		String line = fileLoader.getLine();
		for(auto res : Interpreter::launch(line))
		{
			results.push_back(res);
		}
		fileLoader.next();
	}
	linkedFiles.clear();
	return results;
}

FileLoader& Interpreter::getFileLoader()
{
	return fileLoader;
}

FileLoader& Interpreter::getMainFileLoader()
{
	return *Interpreter::mainFileLoader;
}

void Interpreter::setCommentarySymbol(string symbol)
{
	commentarySymbols.push_back(symbol);
}

Command& Interpreter::preIntCommand(string name)
{
	if(name.size() and name[0] != '#') name = "#" + name;
	if(isPreInt(name)) return *preIntCommands[name];
	IndependantCommand *c = new IndependantCommand(name);
	preIntCommands[name] = c;
	return *c;
}

Command& Interpreter::attributedCommand(string name)
{
	string cid = to_string(reinterpret_cast<uintptr_t>(this)) + name;
	if(Command::isCommand(cid))
	{
		return Command::getCommand(cid);
	}
	Command *c = new Command(cid);
	attributedCommands.push_back(c);
	return *c;
}

