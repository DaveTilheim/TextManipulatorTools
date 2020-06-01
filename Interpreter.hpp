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
	bool ignore = false;
	vector<string> ignoreFilter;
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
	void setIgnore(bool s);
	bool getIgnore() { return ignore; }
	void addFilterElement(string f);
};

#endif