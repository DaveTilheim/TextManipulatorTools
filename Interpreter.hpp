#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "Command.hpp"
#include "FileLoader.hpp"
#include <stdint.h>

class Interpreter
{
private:
	static FileLoader *mainFileLoader;
	static Interpreter *instance;
	FileLoader fileLoader;
	vector<string> commentarySymbols;
	void preinterpretation();
	void removeCommentary();
	void preIntCommandsRun();
public:
	static FileLoader& getMainFileLoader();
	static Interpreter& get();
	Interpreter();
	~Interpreter();
	vector<string> launchFile(string filename);
	vector<string> launch(string expr);
	void setCommentarySymbol(string symbol);
	bool isPreInt(string str);
	Command& preIntCommand(string name);
	void renamePreInt(string, string name);
	FileLoader& getFileLoader();
};

#endif