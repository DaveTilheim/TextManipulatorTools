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
	unordered_map<string, IndependantCommand *> preIntCommands;
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
	IndependantCommand& preIntCommand(string name);
	Command& attributedCommand(string name);
	void renamePreInt(string, string name);
	void removeAttributed();
};

#endif