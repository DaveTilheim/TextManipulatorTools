#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "Command.hpp"
#include "FileLoader.hpp"
#include <stdint.h>

class Interpreter
{
private:
	static FileLoader *mainFileLoader;
	FileLoader fileLoader;
	map<string, IndependantCommand *> preIntCommands;
	vector<string> linkedFiles;
	vector<string> commentarySymbols;
	vector<const Command *> attributedCommands;
	void preinterpretation();
	void removeCommentary();
	void preIntCommandsRun();
	void setAttributedCommandTag();
	FileLoader& getFileLoader();
public:
	static FileLoader& getMainFileLoader();
	Interpreter();
	~Interpreter();
	vector<string> launchFile(string filename);
	vector<string> launch(string expr);
	void setCommentarySymbol(string symbol);
	bool isPreInt(string str);
	bool alreadyLinked(string filename) const;
	Command& preIntCommand(string name);
	Command& attributedCommand(string name);
	Command& getLinker();
	void renamePreInt(string, string name);
	void removeAttributed();
};

#endif