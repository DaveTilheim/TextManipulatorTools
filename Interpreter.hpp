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
	vector<string> commentarySymbols;
	void preinterpretation();
	void removeCommentary();
	void preIntCommandsRun();
	FileLoader& getFileLoader();
public:
	static FileLoader& getMainFileLoader();
	Interpreter();
	~Interpreter();
	vector<string> launchFile(string filename);
	vector<string> launch(string expr);
	void setCommentarySymbol(string symbol);
	bool isPreInt(string str);
	Command& preIntCommand(string name);
	void renamePreInt(string, string name);
};

#endif