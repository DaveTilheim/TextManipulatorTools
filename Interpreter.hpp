#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "Command.hpp"
#include "FileReader.hpp"

class Interpreter
{
private:
	static FileReader *mainFileReader;
	FileReader fileReader;
	map<string, IndependantCommand *> preIntCommands;
	vector<string> linkedFiles;
	vector<string> commentarySymbols;
	void preinterpretation();
	void removeCommentary();
	void preIntCommandsRun();
	void setAttributedCommandTag();
	FileReader& getFileReader();
public:
	static FileReader& getMainFileReader();
	Interpreter();
	~Interpreter();
	vector<string> launchFile(string filename);
	vector<string> launch(string expr);
	void setCommentarySymbol(string symbol);
	bool isPreInt(string str);
	bool alreadyLinked(string filename) const;
	Command& preIntCommand(string name);
	Command& attributedCommand(string name) const;
};

#endif