#include "Lizzy.hpp"


//Interpreter Lizzy::LizzyPkg::lizzyInt = Interpreter();
Interpreter *Lizzy::LizzyPkg::pLizzyInt = nullptr;
Lizzy::Memory *Lizzy::LizzyPkg::memoryContext = nullptr;

_def_pre(Lizzy::LizzyPkg::load_package_1)
{
	string pkg = args("name");
	try
	{
		Package::getPackage(pkg).load();
	}
	catch(const PackageAlreadyExistsException& e)
	{
		//cout << "%%ignore #load " << pkg << endl;
	}
	return pkg;
}

_def_pre(Lizzy::LizzyPkg::load_package_0)
{
	args.namedArgList["name"] = "Lizzy";
	return Lizzy::LizzyPkg::load_package_1(args);
}

_def_pre(Lizzy::LizzyPkg::load_symbol_commentary)
{
	for(auto symbol : args.list())
	{
		pLizzyInt->setCommentarySymbol(symbol);
	}
	return to_string(args.list().size());
}



_def_action(Lizzy::LizzyPkg::use_file_action)
{
	return Lizzy::LangPkg::use_file_action(args);
}

_def_action(Lizzy::LizzyPkg::int_action)
{
	string cmd = args.list();
	string buf;
	for(string s : pLizzyInt->launch(cmd))
	{
		buf += s + " ";
	}
	if(buf.size()) buf.pop_back();
	else buf = " ";
	return buf;
}

unsigned long Lizzy::LizzyPkg::blockCounter = 0;
bool allowedElse=false;

_def_action(Lizzy::LizzyPkg::if_action)
{
	allowedElse = true;
	if(pLizzyInt->getIgnore())
	{
		blockCounter++;
	}
	else
	{
		string arg = args.list();
		bool result = memoryContext->evaluate(arg);
		if(result)
		{
			memoryContext->push(".");
		}
		else
		{
			pLizzyInt->setIgnore(true);
		}
	}
	return "/";
}

_def_action(Lizzy::LizzyPkg::end_if_action)
{
	allowedElse = true;
	if(pLizzyInt->getIgnore())
	{
		if(not blockCounter)
		{
			pLizzyInt->setIgnore(false);
		}
		blockCounter--;
	}
	else
	{
		memoryContext->pop();
	}
	return "/";
}


_def_action(Lizzy::LizzyPkg::else_action)
{
	if(not allowedElse) throw Exception("else not allowed here");
	allowedElse = false;
	if(pLizzyInt->getIgnore())
	{
		if(not blockCounter)
		{
			pLizzyInt->setIgnore(false);
			memoryContext->push(".");
		}
	}
	else
	{
		memoryContext->pop();
		pLizzyInt->setIgnore(true);
	}
	return "/";
}

_def_action(Lizzy::LizzyPkg::elif_action)
{
	if(not allowedElse) throw Exception("elif not allowed here");
	if(pLizzyInt->getIgnore())
	{
		
		if(not blockCounter)
		{
			string arg = args.list();
			bool result = memoryContext->evaluate(arg);
			if(result)
			{
				pLizzyInt->setIgnore(false);
				memoryContext->push(".");
			}
		}
	}
	else
	{
		memoryContext->pop();
		pLizzyInt->setIgnore(true);
	}
	return "/";
}


Lizzy::LizzyPkg::LizzyPkg() : Package("Lizzy")
{
	CALL_ONCE
	pLizzyInt = &lizzyInt;
	lizzyInt.setCommentarySymbol("//");
	addSubPackage(new Lizzy::InfoPkg());
	addSubPackage(new Lizzy::StdPkg());
	addSubPackage(new Lizzy::LangPkg());
	memoryContext = Lizzy::MemPkg::_memoryContext;

	Action load_package_0Action(load_package_0);
	Action load_package_1Action(load_package_1);
	Action loadSymbolCommentaryAction(load_symbol_commentary);
	load_package_1Action.setNamed("name");

	lizzyInt.preIntCommand("load").child("package").setAction(0, load_package_0Action);
	lizzyInt.preIntCommand("load").child("package").setAction(1, load_package_1Action);
	lizzyInt.preIntCommand("load").child("symbol").child("commentary").setAction(-1, loadSymbolCommentaryAction);

	Action useFileAction(use_file_action);
	useFileAction.setNamed("*file");
	lizzyInt.preIntCommand("use").child("file").setAction(1, useFileAction);

	Action intAction(int_action);


	Action ifAction(if_action);
	cmd("if").setAction(1, ifAction);
	Action endifAction(end_if_action);
	cmd("end").child("if").setAction(0, endifAction);
	Action elseAction(else_action);
	cmd("else").setAction(0, elseAction);
	Action elifAction(elif_action);
	cmd("else").child("if").setAction(1, elifAction);
	pLizzyInt->addFilterElement("if");
	pLizzyInt->addFilterElement("end");
	pLizzyInt->addFilterElement("else");
	pLizzyInt->addFilterElement("elif");

	cmdAlias(cmd("else").child("if"), "elif");


	cmd("int").setAction(1, intAction);
}

void Lizzy::LizzyPkg::load()
{
	CALL_ONCE
	loadSubPackages();

}
