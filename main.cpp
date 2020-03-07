#include "Tokens.hpp"

int main(int argc, char const *argv[])
{
	Tokens toks;
	ifstream file("main.cpp");

	while(toks.read(file))
	{
		toks.foreach([](String& s)
		{
			s.remove("\t");
		});
		toks.clean();
		if(toks.size())
			cout << toks << endl;
	}

	file.close();





	return 0;
}
